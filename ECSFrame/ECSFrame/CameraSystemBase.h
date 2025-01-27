/**
* @file   CameraSystemBase.h
* @brief  �J�����V�X�e�����N���X��`.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _CAMERA_SYSTEM_BASE_H_
#define _CAMERA_SYSTEM_BASE_H_

#include <DirectXMath.h>

#include "SystemBase.h"
#include "Transform.h"
#include "IEntityOperator.h"
#include "IChunkProvider.h"

namespace HaraProject::Framework {
class ISystemDistributor;
class CameraSystemBase : public SystemBase
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	CameraSystemBase(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);
	
	/**
	* @brief �f�X�g���N�^
	*/
	~CameraSystemBase();

	/**
	* @brief �r���[�ϊ��s��擾
	*/
	DirectX::XMFLOAT4X4 GetViewMatrix(bool isTranspose = true);

	/**
	* @brief �v���W�F�N�V�����ϊ��s��擾
	*/
	DirectX::XMFLOAT4X4 GetProjectionMatrix(bool isTranspose = true);

	/**
	* @brief 3D�p��
	*/
	bool Is3D();

	/**
	* @brief ����p�擾
	*/
	float GetFovy();

	/**
	* @brief �����擾
	*/
	float GetWidth();

	/**
	* @brief �őO�ʎ擾
	*/
	float GetNear();

	/**
	* @brief �ŉ��ʎ擾
	*/
	float GetFar();

	/**
	* @brief 
	*/
	float GetAspect();

	/**
	* @brief 
	*/
	float GetFocus();

	/**
	* @brief �����_�擾
	*/
	DirectX::XMFLOAT3 GetLook();

	/**
	* @brief �O���x�N�g���擾
	*/
	DirectX::XMFLOAT3 GetFront();

	/**
	* @brief �E�����x�N�g���擾
	*/
	DirectX::XMFLOAT3 GetRight();

	/**
	* @brief ������x�N�g���擾
	*/
	DirectX::XMFLOAT3 GetUp();

	/**
	* @brief �ʒu�擾
	*/
	DirectX::XMFLOAT3 GetPosition();

	/**
	* @brief �ʒu�ݒ�
	* @param[in] position ���W
	*/
	void SetPosition(DirectX::XMFLOAT3 position);

	/**
	* @brief �v���W�F�N�V�����ݒ�
	* @param[in] is3D �������e��
	*/
	void SetIs3D(bool is3D);

protected:
	bool m_is_3d;
	float m_fovy;
	float m_width;
	float m_aspect, m_near, m_far;
	float m_focus;

	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT4 m_quaternion;
};
}// namespace HaraProject::Framework

#endif // !_CAMERA_SYSTEM_BASE_H_