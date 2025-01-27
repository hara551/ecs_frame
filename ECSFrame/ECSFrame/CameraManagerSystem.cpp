#include <unordered_map>

#include "CameraManagerSystem.h"
#include "SystemBase.h"

namespace HaraProject::Framework {


/**
* @brief コンストラクタ
*/
CameraManagerSystem::CameraManagerSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
	: SystemBase(entityOperator, systemDistributor, chunkProvider)
	, m_main_camera(nullptr)
	, m_ui_camera(nullptr)
	, m_ui_front_camera(nullptr)
{
}

/**
* @brief デストラクタ
*/
CameraManagerSystem::~CameraManagerSystem()
{
	ReleaseAllCameras();
}

/**
* @brief システム更新
*/
void CameraManagerSystem::UpdateSystem(float deltaTime)
{
	// 全カメラ更新
	for (const auto& camera : m_name_to_camera)
	{
		if (camera.second != nullptr)
		{
			camera.second->UpdateSystem(deltaTime);
		}
	}
}

/**
* @brief カメラを取得
* @param[in] cameraType カメラの種類
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
* @brief カメラを解放
* @param[in] cameraSystemName カメラ名
*/
void CameraManagerSystem::ReleaseCamera(std::string cameraSystemName)
{
	if (!m_name_to_camera.contains(cameraSystemName))return;

	// 該当カメラを解放して要素も削除
	delete m_name_to_camera[cameraSystemName];
	std::erase_if(m_name_to_camera,
		[cameraSystemName](auto& itr)
		{
			return itr.first == cameraSystemName;
		});
}

/**
* @brief 全カメラを解放
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
* @brief カメラを変更
* @param[in] cameraType カメラ種類
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
