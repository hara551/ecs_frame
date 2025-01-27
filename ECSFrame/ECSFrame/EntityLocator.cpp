#include "EntityLocator.h"

namespace HaraProject::Framework
{

/**
* @brief 格納位置登録
* @param[in] id エンティティID
* @param[in] chunk チャンクへのポインタ
* @param[in] indexInChunk チャンク内のインデックス
*/
void EntityLocator::RegisterLocation(uint32_t id, ComponentDataChunk* chunk, uint32_t indexInChunk)
{
	m_id_to_location[id] = EntityLocation{ chunk,indexInChunk };
}

/**
* @brief 格納位置登録
* @param[in] id エンティティID
*/
EntityLocator::EntityLocation EntityLocator::GetLocation(uint32_t id)
{
	if (m_id_to_location.contains(id))
	{
		return m_id_to_location[id];
	}
	return EntityLocation{};
}

}// !namespace HaraProject::Framework