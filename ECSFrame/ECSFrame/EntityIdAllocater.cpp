#include <cstdint>

#include "ComponentMask.h"
#include "EditDataUtil.h"

#include "EntityIdAllocater.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
EntityIdAllocater::EntityIdAllocater()
	: m_next_id(0)
{
}

/**
* @brief エンティティIDを空ける
* @param[in] id エンティティID
*/
void EntityIdAllocater::FreeUpId(uint32_t id)
{
	// 有効とするバージョンを上げる
	IncreaceValidVersion(id);

	// フリーIDとして追加
	m_free_ids.push_back(id);
}

/**
* @brief 使えるIDを割り当てる
*/
EntityIdAllocater::EntityHandle EntityIdAllocater::AssignUsableId()
{
	EntityHandle entity_handle{};
	// 空きIDがあれば再利用
	if (!m_free_ids.empty())
	{
		entity_handle.id = m_free_ids.front();
		m_free_ids.erase(m_free_ids.begin());

		entity_handle.version = m_latest_versions[entity_handle.id];
		return entity_handle;
	}

	// 無ければ新しく発行
	return IssueNewId();
}

/**
* @brief 新しくIDを発行する
*/
EntityIdAllocater::EntityHandle EntityIdAllocater::IssueNewId()
{
	// 新しくIDを作成
	EntityHandle entity_handle{ m_next_id, 0 };
	// バージョンリストに追加
	m_latest_versions.push_back(0);

	++m_next_id;

	return entity_handle;
}

/**
* @brief IDが有効か
* @param[in] id エンティティID
* @param[in] version バージョン
*/
bool EntityIdAllocater::IsValidId(uint32_t id, uint32_t version)
{
	return m_latest_versions[id] == version;
}

/**
* @brief 有効とするバージョンを上げる
* @param[in] エンティティID
*/
uint32_t EntityIdAllocater::IncreaceValidVersion(uint32_t id)
{
	if (m_latest_versions.size() - 1 >= id)
	{
		return ++m_latest_versions[id];
	}
	return 0;
}

}// !namespace HaraProject::Framework