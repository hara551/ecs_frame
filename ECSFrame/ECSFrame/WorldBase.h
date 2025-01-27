/**
* @file   WorldBase.h
* @brief  ECS管理単位クラス定義.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _WORLD_BASE_H_
#define _WORLD_BASE_H_

#include <string>
#include <mutex>

#include "ComponentDataManager.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "IEditDataLoader.h"

namespace HaraProject::Framework {

class WorldBase
{
public:
	/**
	* @brief コンストラクタ
	* @param[in] worldName ワールド名
	*/
	WorldBase(std::string worldName);

	/**
	* @brief デストラクタ
	*/
	virtual ~WorldBase();

	/**
	* @brief ワールド更新処理
	*/
	void UpdateWorld(float deltaTime);

	/**
	* @brief ワールド描画処理
	*/
	void DrawWorld();

	/**
	* @brief ロードが完了したか確認
	*/
	bool IsCompleteLoad();

	/**
	* @brief ワールド名取得
	*/
	std::string GetName();

	/**
	* @brief エンティティマネージャー取得
	*/
	EntityManager* GetEntityManager() {
		return m_entity_manager;
	}

	/**
	* @brief コンポーネントデータマネージャー取得
	*/
	ComponentDataManager* GetComponentDataManager() {
		return m_component_data_manager;
	}

	/**
	* @brief システムマネージャー取得
	*/
	SystemManager* GetSystemManager() {
		return m_system_manager;
	}

protected:
	/**
	* @brief ワールド初期化処理
	*/
	virtual void InitWorld();

	/**
	* @brief ワールド終了処理
	*/
	virtual void UninitWorld();

	/**
	* @brief 既定のシステムを登録
	*/
	void RegisterWorldSystems();

	/**
	* @brief ワールドのエンティティを全て作成
	*/
	void CreateEntities();

	/**
	* @brief ワールドに必要なリソースをロード
	*/
	void LoadWorldResources();

	/**
	* @brief リソースを必要なエンティティにセットする
	*/
	void SettingResourcesToEntity();

	/**
	* @brief ワールド名
	*/
	std::string m_world_name;

	/**
	* @brief ロード中のリソース数
	*/
	int32_t m_num_resource_loading;

	/**
	* @brief ロード進捗確認報告用ロック
	*/
	std::mutex m_loaded_sign_mutex;

	/**
	* @brief コンポーネントデータ管理
	*/
	ComponentDataManager* m_component_data_manager;

	/**
	* @brief エンティティ管理
	*/
	EntityManager* m_entity_manager;

	/**
	* @brief システム管理
	*/
	SystemManager* m_system_manager;

	/**
	* @brief 編集データの読み込みインタフェース
	*/
	IEditDataLoader* m_edit_data_loder;
};

} // !namespace HaraProject::Framework

#endif // !_WORLD_BASE_H_
