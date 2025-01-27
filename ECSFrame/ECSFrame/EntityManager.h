/**
* @file   EntityManager.h
* @brief  エンティティ制御クラス定義.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include <cstdint>
#include <unordered_map>

#include "EntityIdAllocater.h"
#include "EntityLocator.h"
#include "EntityValueHandler.h"
#include "ComponentDataChunk.h"
#include "IComponentDataManager.h"

#include "IEntityOperator.h"
#include "IEntityVersionChecker.h"

#ifdef _DEBUG
#include "nlohmann/json.hpp"
#include "GuiItemBase.h"
#include "GuiManager.h"
#endif // _DEBUG

namespace HaraProject::Framework
{

class EntityManager : public IEntityOperator, public IEntityVersionChecker
{
public:
	/**
	* @brief コンストラクタ
	* @param[in] componentDataManager コンポーネントデータマネージャー
	*/
	EntityManager(IComponentDataManager* componentDataManager);

	/**
	* @brief 読み込んだエンティティを作成する
	* @param[in] entityValueHandler 値が格納されたエンティティのデータ
	*/
	uint32_t CreateLoadedEntity(std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler)override;

	/**
	* @brief エンティティを削除する
	* @param[in] id エンティティID
	*/
	void DeleteEntity(uint32_t id)override;

	/**
	* @brief エンティティにコンポーネントデータを追加
	* @param[in] id エンティティID
	* @param[in] bit コンポーネント識別ビット
	*/
	void AddComponentData(uint32_t id, ComponentBits bit)override;

	/**
	* @brief エンティティからコンポーネントを削除
	* @param[in] id エンティティID
	* @param[in] bit コンポーネント識別ビット
	*/
	void RemoveComponentData(uint32_t id, ComponentBits bit)override;

	/**
	* @brief エンティティからコンポーネントを取得
	* @param[in] id エンティティID
	* @param[in] bit コンポーネント識別ビット
	*/
	ComponentDataBase* GetComponentData(uint32_t id, ComponentBits bit)override;

	/**
	* @brief エンティティが指定コンポーネントを持っているか確認
	* @param[in] id エンティティID
	* @param[in] bit コンポーネント識別ビット
	*/
	bool HasComponentData(uint32_t id, ComponentBits bit)override;

	/**
	* @brief 有効なエンティティか
	* @param[in] id エンティティID
	* @param[in] version バージョン
	*/
	bool IsValidEntity(uint32_t id, uint32_t version)override;

#ifdef _DEBUG
	/**
	* @brief 空のエンティティを作成
	*/
	uint32_t CreateEntityEmpty()override;

	/**
	* @brief エンティティのデータをJsonに変換
	* @param[in] id エンティティID
	*/
	nlohmann::json ConvertEntityToJson(uint32_t id);

	/**
	* @brief エンティティのデータを取得
	* @param[in] id エンティティID
	*/
	std::unordered_map<ComponentBits, ComponentDataBase*> GetEntityData(uint32_t id);
#endif // _DEBUG


private:
	/**
	* @brief エンティティID管理
	*/
	EntityIdAllocater m_entity_id_allocater;

	/**
	* @brief エンティティ格納位置管理
	*/
	EntityLocator m_entity_locator;

	/**
	* @brief コンポーネントデータ管理
	*/
	IComponentDataManager* m_component_data_manager;
};

}// !namespace HaraProject::Framework

#endif // !_ENTITY_MANAGER_H_