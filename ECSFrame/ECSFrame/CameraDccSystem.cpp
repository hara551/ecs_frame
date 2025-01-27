#include <DirectXMath.h>

#include "CameraSystemBase.h"
#include "Input.h"

#include "CameraDccSystem.h"

namespace HaraProject::Framework {

/**
* @brief ������
*/
enum CameraDCCKind
{
	CAM_DCC_NONE = 0,
	CAM_DCC_ORBIT,
	CAM_DCC_TRACK,
	CAM_DCC_DOLLY,
	CAM_DCC_FLIGHT,
};

/**
* @brief �R���X�g���N�^
*/
CameraDccSystem::CameraDccSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
	: CameraSystemBase(entityOperator, systemDistributor, chunkProvider)
	, _state(CAM_DCC_NONE)
	, _oldPosition{ 0, 0 }
{
}

void CameraDccSystem::UpdateSystem(float deltaTime)
{
	UpdateState();
	if (_state == CAM_DCC_NONE) return;

	Argument arg;
	// �}�E�X�ړ���
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	arg.mouseMove = DirectX::XMFLOAT2((float)cursorPos.x - _oldPosition.x, (float)cursorPos.y - _oldPosition.y);

	_oldPosition = cursorPos;
	// �J�������
	DirectX::XMFLOAT3 front = GetFront();
	DirectX::XMFLOAT3 side = GetRight();
	DirectX::XMFLOAT3 up(0.0f, 1.0f, 0.0f);
	DirectX::XMFLOAT3 look = GetLook();
	arg.vCamFront = DirectX::XMLoadFloat3(&front);
	arg.vCamSide = DirectX::XMLoadFloat3(&side);
	arg.vCamPos = DirectX::XMLoadFloat3(&m_position);
	arg.vCamLook = DirectX::XMLoadFloat3(&look);
	arg.vCamUp = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(arg.vCamFront, arg.vCamSide));

	switch (_state)
	{
	case CAM_DCC_ORBIT:		UpdateOrbit(arg);	break;
	case CAM_DCC_TRACK:		UpdateTrack(arg);	break;
	case CAM_DCC_DOLLY:		UpdateDolly(arg);	break;
	case CAM_DCC_FLIGHT:	UpdateFlight(arg);	break;
	}
}

void CameraDccSystem::UpdateState()
{
	CameraDCCKind prev = (CameraDCCKind)_state;
	if (IsKeyPress(VK_MENU))
	{
		_state = CAM_DCC_NONE;
		if (IsKeyPress(VK_LBUTTON)) _state = CAM_DCC_ORBIT;
		if (IsKeyPress(VK_MBUTTON)) _state = CAM_DCC_TRACK;
		if (IsKeyPress(VK_RBUTTON)) _state = CAM_DCC_DOLLY;
	}
	else if (IsKeyPress(VK_RBUTTON))
	{
		_state = CAM_DCC_FLIGHT;
	}
	else
	{
		_state = CAM_DCC_NONE;
	}
	if (prev != _state)
	{
		GetCursorPos(&_oldPosition);
	}
}

void CameraDccSystem::UpdateOrbit(Argument& arg)
{
	// �}�E�X�̈ړ��� / ��ʃT�C�Y �̔䗦����A��ʑS�̂łǂꂾ����]���邩�w�肷��
	float angleX = 360.0f * arg.mouseMove.x / 1280.0f;
	float angleY = 180.0f * arg.mouseMove.y / 720.0f;

	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
		DirectX::XMVectorSet(0, 1, 0, 0), DirectX::XMConvertToRadians(angleX)
	);
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quaternion);
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	DirectX::XMVECTOR vAxisX = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	vAxisX = DirectX::XMVector3Rotate(vAxisX, qRotate);
	quat = DirectX::XMQuaternionRotationAxis(vAxisX, DirectX::XMConvertToRadians(angleY));
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	DirectX::XMStoreFloat4(&m_quaternion, qRotate);

	// �����_����J�����̌���փt�H�[�J�X���������ړ�������
	DirectX::XMFLOAT3 dir = GetFront();
	DirectX::XMVECTOR vDir = DirectX::XMLoadFloat3(&dir);
	vDir = DirectX::XMVectorScale(vDir, -GetFocus());
	DirectX::XMVECTOR vPos = DirectX::XMVectorAdd(arg.vCamLook, vDir);
	DirectX::XMStoreFloat3(&m_position, vPos);
}

void CameraDccSystem::UpdateTrack(Argument& arg)
{
	float fClip = GetFar();

	// ����A�A���B�Ƃ���O�p�`�ɂ��� tan�� = A / B�����藧��
	// ��L�������ƂɊ���o�������i�̍������A�ړ��� / ��ʃT�C�Y �̔䗦����A�ړ��ʂƂ��ċ��߂�
	float width = GetFovy();
	float farScreenHeight = tanf(width * 0.5f) * fClip;
	float screenRateW = arg.mouseMove.x / 640.0f;
	float screenRateH = arg.mouseMove.y / 360.0f;
	float farMoveX = -farScreenHeight * screenRateW * GetAspect();
	float farMoveY = farScreenHeight * screenRateH;

	// �J�����̎p�������ƂɈړ�
	float rate = GetFocus() / fClip;
	DirectX::XMVECTOR vCamMove = DirectX::XMVectorZero();
	vCamMove = DirectX::XMVectorAdd(vCamMove, DirectX::XMVectorScale(arg.vCamSide, farMoveX * rate));
	vCamMove = DirectX::XMVectorAdd(vCamMove, DirectX::XMVectorScale(arg.vCamUp, farMoveY * rate));
	DirectX::XMStoreFloat3(&m_position, DirectX::XMVectorAdd(arg.vCamPos, vCamMove));
}

void CameraDccSystem::UpdateDolly(Argument& arg)
{
	float focus = GetFocus();
	float fClip = GetFar();
	float nClip = GetNear();

	// �t�H�[�J�X�ʒu�ƃN���b�v�ʂ̈ʒu�ɉ����ĕ␳�ړ��ʂ��v�Z
	float clipDistance = fClip - nClip;
	float rate = (focus - nClip) / clipDistance;

	// �ړ���
	float move = rate * (arg.mouseMove.x + arg.mouseMove.y) * fClip * 0.01f;
	focus = std::min(fClip, std::max(nClip, focus - move));

	// �J�����ʒu�X�V
	DirectX::XMVECTOR vMove = DirectX::XMVectorScale(arg.vCamFront, -focus);
	DirectX::XMStoreFloat3(&m_position, DirectX::XMVectorAdd(arg.vCamLook, vMove));
	m_focus = focus;
}

void CameraDccSystem::UpdateFlight(Argument& arg)
{
	// �}�E�X�̈ړ��� / ��ʃT�C�Y �̔䗦����A��ʑS�̂łǂꂾ����]���邩�w�肷��B
	float angleX = 360.0f * arg.mouseMove.x / 1280.0f;
	float angleY = 180.0f * arg.mouseMove.y / 720.0f;

	// ����]
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quaternion);
	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
		arg.vCamUp, DirectX::XMConvertToRadians(angleX)
	);
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	// �c��]
	DirectX::XMVECTOR vAxis = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	vAxis = DirectX::XMVector3Rotate(vAxis, qRotate);
	quat = DirectX::XMQuaternionRotationAxis(vAxis, DirectX::XMConvertToRadians(angleY));
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	// ��]�̍X�V
	DirectX::XMStoreFloat4(&m_quaternion, qRotate);

	// ���̎擾
	DirectX::XMFLOAT3 front = GetFront();
	DirectX::XMFLOAT3 side = GetRight();
	arg.vCamFront = DirectX::XMLoadFloat3(&front);
	arg.vCamSide = DirectX::XMLoadFloat3(&side);

	// �L�[���͂ňړ�
	DirectX::XMVECTOR vCamMove = DirectX::XMVectorZero();
	if (IsKeyPress('W')) vCamMove = DirectX::XMVectorAdd(vCamMove, arg.vCamFront);
	if (IsKeyPress('S')) vCamMove = DirectX::XMVectorSubtract(vCamMove, arg.vCamFront);
	if (IsKeyPress('A')) vCamMove = DirectX::XMVectorSubtract(vCamMove, arg.vCamSide);
	if (IsKeyPress('D')) vCamMove = DirectX::XMVectorAdd(vCamMove, arg.vCamSide);
	if (IsKeyPress('Q')) vCamMove = DirectX::XMVectorAdd(vCamMove, DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	if (IsKeyPress('E')) vCamMove = DirectX::XMVectorAdd(vCamMove, DirectX::XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f));
	vCamMove = DirectX::XMVectorScale(vCamMove, GetFar() * 0.02f);

	// �X�V
	DirectX::XMVECTOR vCamPos = DirectX::XMVectorAdd(arg.vCamPos, vCamMove);
	DirectX::XMStoreFloat3(&m_position, vCamPos);
}
}// namespace HaraProject::Framework

