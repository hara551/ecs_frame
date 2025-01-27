#include <unordered_map>

#include "CameraManagerSystem.h"
#include "SystemBase.h"

namespace HaraProject::Framework {


/**
* @brief �R���X�g���N�^
*/
CameraManagerSystem::CameraManagerSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
	: SystemBase(entityOperator, systemDistributor, chunkProvider)
	, m_main_camera(nullptr)
	, m_ui_camera(nullptr)
	, m_ui_front_camera(nullptr)
{
}

/**
* @brief �f�X�g���N�^
*/
CameraManagerSystem::~CameraManagerSystem()
{
	ReleaseAllCameras();
}

/**
* @brief �V�X�e���X�V
*/
void CameraManagerSystem::UpdateSystem(float deltaTime)
{
	// �S�J�����X�V
	for (const auto& camera : m_name_to_camera)
	{
		if (camera.second != nullptr)
		{
			camera.second->UpdateSystem(deltaTime);
		}
	}
}

/**
* @brief �J�������擾
* @param[in] cameraType �J�����̎��
*/
CameraSystemBase* CameraManagerSystem::GetCamera(CameraType cameraType)
{
	switch (cameraType)
	{
	case MainCamera:
		return m_main_camera;
		break;
	case UICamera:
		return m_ui_camera;
		break;
	case UIFrontCamera:
		return m_ui_front_camera;
		break;
	}
	return nullptr;
}

/**
* @brief �J���������
* @param[in] cameraSystemName �J������
*/
void CameraManagerSystem::ReleaseCamera(std::string cameraSystemName)
{
	if (!m_name_to_camera.contains(cameraSystemName))return;

	// �Y���J������������ėv�f���폜
	delete m_name_to_camera[cameraSystemName];
	std::erase_if(m_name_to_camera,
		[cameraSystemName](auto& itr)
		{
			return itr.first == cameraSystemName;
		});
}

/**
* @brief �S�J���������
*/
void CameraManagerSystem::ReleaseAllCameras()
{
	for (auto& camera : m_name_to_camera)
	{
		if (camera.second != nullptr)
		{
			delete camera.second;
			camera.second = nullptr;
		}
	}
	m_name_to_camera.clear();
	m_main_camera = nullptr;
	m_ui_camera = nullptr;
	m_ui_front_camera = nullptr;
}

/**
* @brief �J������ύX
* @param[in] cameraType �J�������
* @param[in] cameraSystemName
*/
void CameraManagerSystem::ChangeCamera(CameraType cameraType, std::string cameraSystemName)
{
	if (!m_name_to_camera.contains(cameraSystemName))return;
	
	switch (cameraType)
	{
	case MainCamera:
		m_main_camera = m_name_to_camera[cameraSystemName];
		break;
	case UICamera:
		m_ui_camera = m_name_to_camera[cameraSystemName];
		break;
	case UIFrontCamera:
		m_ui_front_camera = m_name_to_camera[cameraSystemName];
		break;
	}
}

}// namespace HaraProject::Framework
