/**
* @file   CameraManager.h
* @brief  カメラ管理システム定義.
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
* @brief カメラ管理クラス
*/
class CameraManagerSystem : public SystemBase
{
public:
	/**
	* @brief 登録用システム名
	*/
	static inline const char* CAMERA_MANAGER_SYSTEM = "CameraManagerSystem";

	/**
	* @brief カメラ種類
	*/
	enum CameraType
	{
		MainCamera,
		UICamera,
		UIFrontCamera
	};

	/**
	* @brief コンストラクタ
	*/
	CameraManagerSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief デストラクタ
	*/
	~CameraManagerSystem();

	/**
	* @brief システム更新
	*/
	void UpdateSystem(float deltaTime)override;

	/**
	* @brief カメラを取得
	* @param[in] cameraType カメラの種類
	*/
	CameraSystemBase* GetCamera(CameraType cameraType);

	/**
	* @brief カメラを解放
	* @param[in] cameraSystemName カメラ名
	*/
	void ReleaseCamera(std::string cameraSystemName);

	/**
	* @brief 全カメラを解放
	*/
	void ReleaseAllCameras();

	/**
	* @brief カメラを変更
	* @param[in] cameraType カメラ種類
	* @param[in] cameraSystemName
	*/
	void ChangeCamera(CameraType cameraType, std::string cameraSystemName);

	/**
	* @brief カメラを登録
	* @tparam カメラシステム
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
	* @brief メインカメラ
	*/
	CameraSystemBase* m_main_camera;

	/**
	* @brief UIカメラ
	*/
	CameraSystemBase* m_ui_camera;

	/**
	* @brief UIの上に描画するカメラ
	*/
	CameraSystemBase* m_ui_front_camera;

	/**
	* @brief カメラ一覧
	*/
	std::unordered_map<std::string, CameraSystemBase*> m_name_to_camera;
};

}// namespace HaraProject::Framework
#endif // !_CAMERA_MANAGER_SYSTEM_H_