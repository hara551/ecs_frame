#include <DirectXMath.h>

#include "CameraSystemBase.h"
#include "SystemBase.h"
#include "Transform.h"

namespace HaraProject::Framework {

static const float FOVY_DEFAULT = 60.0f;
static const float WIDTH_DEFAULT = 20.0f;
static const float ASPECT_DEFAULT = 16.0f / 9.0f;
static const float NEAR_DEFAULT = 0.2f;
static const float FAR_DEFAULT = 10000.0f;
static const float FOCUS_DEFAULT = 1.0f;

/**
* @brief コンストラクタ
*/
CameraSystemBase::CameraSystemBase(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
	: SystemBase(entityOperator, systemDistributor, chunkProvider)
	, m_is_3d(true)
	, m_fovy(FOVY_DEFAULT), m_width(WIDTH_DEFAULT)
	, m_aspect(ASPECT_DEFAULT), m_near(NEAR_DEFAULT), m_far(FAR_DEFAULT)
	, m_focus(FOCUS_DEFAULT)
	, m_position(0.0f, 0.0f, 0.0f)
	, m_quaternion(0.0f, 0.0f, 0.0f, 1.0f)
{
}

/**
* @brief デストラクタ
*/
CameraSystemBase::~CameraSystemBase()
{
}

/**
* @brief ビュー変換行列取得
*/
DirectX::XMFLOAT4X4 CameraSystemBase::GetViewMatrix(bool isTranspose)
{
	DirectX::XMFLOAT3 pos = m_position;
	DirectX::XMFLOAT3 look = GetLook();
	DirectX::XMFLOAT3 up(0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&pos);
	DirectX::XMVECTOR vLook = DirectX::XMLoadFloat3(&look);
	DirectX::XMVECTOR vUp = DirectX::XMLoadFloat3(&up);
	DirectX::XMMATRIX mat = DirectX::XMMatrixLookAtLH(vPos, vLook, vUp);
	if (isTranspose)
		mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fmat;
	DirectX::XMStoreFloat4x4(&fmat, mat);
	return fmat;
}

/**
* @brief プロジェクション変換行列取得
*/
DirectX::XMFLOAT4X4 CameraSystemBase::GetProjectionMatrix(bool isTranspose)
{
	DirectX::XMMATRIX mat;
	if (m_is_3d) {
		mat = DirectX::XMMatrixPerspectiveFovLH(GetFovy(), m_aspect, m_near, m_far);
	}
	else {
		mat = DirectX::XMMatrixOrthographicLH(m_width, m_width / m_aspect, m_near, m_far);
	}
	if (isTranspose)
		mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fmat;
	DirectX::XMStoreFloat4x4(&fmat, mat);
	return fmat;
}

/**
* @brief 3D用か
*/
bool CameraSystemBase::Is3D()
{
	return m_is_3d;
}

/**
* @brief 視野角取得
*/
float CameraSystemBase::GetFovy()
{
	return DirectX::XMConvertToRadians(m_fovy);
}

/**
* @brief 横幅取得
*/
float CameraSystemBase::GetWidth()
{
	return m_width;
}

float CameraSystemBase::GetNear()
{
	return m_near;
}

float CameraSystemBase::GetFar()
{
	return m_far;
}

float CameraSystemBase::GetAspect()
{
	return m_aspect;
}

float CameraSystemBase::GetFocus()
{
	return m_focus;
}

DirectX::XMFLOAT3 CameraSystemBase::GetLook()
{
	// 位置の取得
	DirectX::XMFLOAT3 pos = m_position;
	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&pos);

	// 前方ベクトル取得
	DirectX::XMFLOAT3 front = GetFront();
	DirectX::XMVECTOR vFront = DirectX::XMLoadFloat3(&front);

	// カメラの位置からフォーカス距離まで進んだ位置を注視点とする
	vFront = DirectX::XMVectorScale(vFront, m_focus);
	DirectX::XMVECTOR vLook = DirectX::XMVectorAdd(vPos, vFront);

	DirectX::XMStoreFloat3(&pos, vLook);
	return pos;
}

DirectX::XMFLOAT3 CameraSystemBase::GetFront()
{
	DirectX::XMVECTOR vFront = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quaternion);
	vFront = DirectX::XMVector3Rotate(vFront, qRotate);
	DirectX::XMFLOAT3 dir;
	DirectX::XMStoreFloat3(&dir, DirectX::XMVector3Normalize(vFront));
	return dir;
}

DirectX::XMFLOAT3 CameraSystemBase::GetRight()
{
	DirectX::XMVECTOR vRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quaternion);
	vRight = DirectX::XMVector3Rotate(vRight, qRotate);
	DirectX::XMFLOAT3 dir;
	DirectX::XMStoreFloat3(&dir, DirectX::XMVector3Normalize(vRight));
	return dir;
}

DirectX::XMFLOAT3 CameraSystemBase::GetUp()
{
	DirectX::XMVECTOR vUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quaternion);
	vUp = DirectX::XMVector3Rotate(vUp, qRotate);
	DirectX::XMFLOAT3 dir;
	DirectX::XMStoreFloat3(&dir, vUp);
	return dir;
}

DirectX::XMFLOAT3 CameraSystemBase::GetPosition()
{
	return m_position;
}

void CameraSystemBase::SetPosition(DirectX::XMFLOAT3 position)
{
	m_position = position;
}

void CameraSystemBase::SetIs3D(bool is3D)
{
	m_is_3d = is3D;
}

}// namespace HaraProject::Framework
