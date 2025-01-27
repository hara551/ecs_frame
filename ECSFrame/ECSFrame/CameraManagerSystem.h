/**
* @file   CameraManager.h
* @brief  �J�����Ǘ��V�X�e����`.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _CAMERA_MANAGER_SYSTEM_H_
#define _CAMERA_MANAGER_SYSTEM_H_

#include <unordered_map>
#include <string>

#include "SystemBase.h"
#include "IEntityOperator.h"
#include "ISystemDistributor.h"
#include "IChunkProvider.h"
#include "CameraSystemBase.h"

namespace HaraProject::Framework {


/**
* @brief �J�����Ǘ��N���X
*/
class CameraManagerSystem : public SystemBase
{
public:
	/**
	* @brief �o�^�p�V�X�e����
	*/
	static inline const char* CAMERA_MANAGER_SYSTEM = "CameraManagerSystem";

	/**
	* @brief �J�������
	*/
	enum CameraType
	{
		MainCamera,
		UICamera,
		UIFrontCamera
	};

	/**
	* @brief �R���X�g���N�^
	*/
	CameraManagerSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief �f�X�g���N�^
	*/
	~CameraManagerSystem();

	/**
	* @brief �V�X�e���X�V
	*/
	void UpdateSystem(float deltaTime)override;

	/**
	* @brief �J�������擾
	* @param[in] cameraType �J�����̎��
	*/
	CameraSystemBase* GetCamera(CameraType cameraType);

	/**
	* @brief �J���������
	* @param[in] cameraSystemName �J������
	*/
	void ReleaseCamera(std::string cameraSystemName);

	/**
	* @brief �S�J���������
	*/
	void ReleaseAllCameras();

	/**
	* @brief �J������ύX
	* @param[in] cameraType �J�������
	* @param[in] cameraSystemName
	*/
	void ChangeCamera(CameraType cameraType, std::string cameraSystemName);

	/**
	* @brief �J������o�^
	* @tparam �J�����V�X�e��
	*/
	template<typename T> void RegisterCamera(std::string cameraSystemName)
	{
		if (!m_name_to_camera.contains(cameraSystemName))
		{
			m_name_to_camera[cameraSystemName] = new T(
				m_entity_operator, m_system_distributor, m_chunk_provider
			);
		}
	}

private:
	/**
	* @brief ���C���J����
	*/
	CameraSystemBase* m_main_camera;

	/**
	* @brief UI�J����
	*/
	CameraSystemBase* m_ui_camera;

	/**
	* @brief UI�̏�ɕ`�悷��J����
	*/
	CameraSystemBase* m_ui_front_camera;

	/**
	* @brief �J�����ꗗ
	*/
	std::unordered_map<std::string, CameraSystemBase*> m_name_to_camera;
};

}// namespace HaraProject::Framework
#endif // !_CAMERA_MANAGER_SYSTEM_H_