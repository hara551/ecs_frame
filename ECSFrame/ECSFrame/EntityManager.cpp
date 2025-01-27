
#include "EditDataUtil.h"
#include "EntityIdAllocater.h"
#include "ComponentDataChunk.h"
#include "IComponentDataManager.h"

#include "EntityManager.h"

#include "EntityName.h"
#include "Transform.h"
#include "ComponentMask.h"

namespace HaraProject::Framework
{

/**
* @brief コンストラクタ
* @param[in] componentDataManager コンポーネントデータマネージャー
*/
EntityManager::EntityManager(IComponentDataManager* componentDataManager)
	: m_component_data_manager(componentDataManager)
{
	m_component_data_manager->SetEntityVersionChecker(this);
}

/**
* @brief 読み込んだエンティティを作成する
* @param[in] entityValueHandler 値が格納されたエンティティのデータ
*/
uint32_t EntityManager::CreateLoadedEntity(std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler)
{
	// 利用可能なIDを取得
	EntityIdAllocater::EntityHandle entity_handle =  m_entity_id_allocater.AssignUsableId();

	// エンティティを格納し、格納したチャンクを取得
	ComponentDataChunk* chunk = m_component_data_manager->InsertComponentDataToChunk(
		entity_handle.id, entity_handle.version, entityValueHandler
	);
	// IDからチャンク内のインデックスを取得
	uint32_t indexInChunk = chunk->GetIndex(entity_handle.id);

	// エンティティの格納位置を登録
	m_entity_locator.RegisterLocation(entity_handle.id, chunk, indexInChunk);

	return entity_handle.id;
}

#ifdef _DEBUG
/**
* @brief 空のエンティティを作成
*/
uint32_t EntityManager::CreateEntityEmpty()
{
	// 利用可能なIDを取得
	EntityIdAllocater::EntityHandle entity_handle = m_entity_id_allocater.AssignUsableId();

	std::unordered_map<ComponentBits, ComponentDataBase*> entity_value_handler{};

	// エンティティ名作成
	EntityName* entity_name = new EntityName();
	// デフォルトで名前を設定
	std::string empty_name = "Empty" + std::to_string(entity_handle.id);
	strcpy_s(entity_name->name,empty_name.c_str());

	entity_value_handler[ComponentMask<EntityName>::bit] = entity_name;

	// トランスフォーム作成
	entity_value_handler[ComponentMask<Transform>::bit] = new Transform();

	// エンティティを格納し、格納位置を登録
	ComponentDataChunk* chunk = m_component_data_manager->InsertComponentDataToChunk(
		entity_handle.id, entity_handle.version, entity_value_handler
	);
	uint32_t indexInChunk = chunk->GetIndex(entity_handle.id);

	m_entity_locator.RegisterLocation(entity_handle.id, chunk, indexInChunk);

	// 格納に使ったハンドルを解放
	ReleaceEntityValueHandler(entity_value_handler);

	return entity_handle.id;
}
#endif // _DEBUG

/**
* @brief エンティティを削除する
* @param[in] id エンティティID
*/
void EntityManager::DeleteEntity(uint32_t id)
{
	// 格納位置取得
	EntityLocator::EntityLocation location =  m_entity_locator.GetLocation(id);

	// 所属しているチャンクのバージョンチェックフラグを挙げる
	location.chunk->SetNeedsVersionCheck(true);

	// エンティティIDを空ける
	m_entity_id_allocater.FreeUpId(id);
}

/**
* @brief エンティティにコンポーネントデータを追加
* @param[in] id エンティティID
* @param[in] bit コンポーネント識別ビット
*/
void EntityManager::AddComponentData(uint32_t id, ComponentBits bit)
{
	// 格納位置取得
	EntityLocator::EntityLocation location = m_entity_locator.GetLocation(id);

	// チャンクを移動することになるためバージョンを更新し取得
	uint32_t new_version = m_entity_id_allocater.IncreaceValidVersion(id);

	// コンポーネントデータの追加を依頼し、移動先のチャンクを取得
	ComponentDataChunk* located_chunk = m_component_data_manager->AddComponentData(
		id, new_version, location.chunk, location.indexInChunk, bit
	);
	// 格納されたインデックスを取得
	uint32_t indexInChunk = located_chunk->GetIndex(id);
	// 格納位置を登録
	m_entity_locator.RegisterLocation(id, located_chunk, indexInChunk);
}

/**
* @brief エンティティからコンポーネントを削除
* @param[in] id エンティティID
* @param[in] bit コンポーネント識別ビット
*/
void EntityManager::RemoveComponentData(uint32_t id, ComponentBits bit)
{
	// 格納位置取得
	EntityLocator::EntityLocation location = m_entity_locator.GetLocation(id);

	// チャンクを移動することになるためバージョンを更新し取得
	uint32_t new_version = m_entity_id_allocater.IncreaceValidVersion(id);

	// コンポーネントデータの削除を依頼し、移動先のチャンクを取得
	ComponentDataChunk* located_chunk = m_component_data_manager->RemoveComponentData(
		id, new_version, location.chunk, location.indexInChunk, bit
	);
	// 格納されたインデックスを取得
	uint32_t indexInChunk = located_chunk->GetIndex(id);
	// 格納位置を登録
	m_entity_locator.RegisterLocation(id, located_chunk, indexInChunk);
}

/**
* @brief エンティティからコンポーネントを取得
* @param[in] id エンティティID
* @param[in] bit コンポーネント識別ビット
*/
ComponentDataBase* EntityManager::GetComponentData(uint32_t id, ComponentBits bit)
{
	EntityLocator::EntityLocation location = m_entity_locator.GetLocation(id);

	ComponentDataBase* component_data{};
	if (location.chunk != nullptr)
	{
		component_data = location.chunk->CalculateComponentDataPointer(bit, location.indexInChunk);
	}

	return component_data;
}

/**
* @brief エンティティが指定コンポーネントを持っているか確認
* @param[in] id エンティティID
* @param[in] bit コンポーネント識別ビット
*/
bool EntityManager::HasComponentData(uint32_t id, ComponentBits bit)
{
	ComponentDataBase* component = GetComponentData(id, bit);
	return component != nullptr;
}

/**
* @brief 有効なエンティティか
* @param[in] id エンティティID
* @param[in] version バージョン
*/
bool EntityManager::IsValidEntity(uint32_t id, uint32_t version)
{
	return m_entity_id_allocater.IsValidId(id, version);
}

#ifdef _DEBUG
/**
* @brief エンティティのデータをJsonに変換
* @param[in] id エンティティID
*/
nlohmann::json EntityManager::ConvertEntityToJson(uint32_t id)
{
	EntityLocator::EntityLocation location = m_entity_locator.GetLocation(id);

	std::unordered_map<ComponentBits, ComponentDataBase*> entity_data_handle = location.chunk->GetEntityData(location.indexInChunk);

	nlohmann::json entity_json_data{};
	for (const auto& component : entity_data_handle)
	{
		entity_json_data.merge_patch(component.second->WriteDataToJson());
	}

	// 使用したハンドルを解放
	ReleaceEntityValueHandler(entity_data_handle);

	return entity_json_data;
}

/**
* @brief エンティティのデータを取得
* @param[in] id エンティティID
*/
std::unordered_map<ComponentBits, ComponentDataBase*> EntityManager::GetEntityData(uint32_t id)
{
	EntityLocator::EntityLocation location = m_entity_locator.GetLocation(id);
	return location.chunk->GetEntityData(location.indexInChunk);
}
#endif // _DEBUG

}// !namespace HaraProject::Framework