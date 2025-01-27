/**
* @file   EntityLocator.h
* @brief  エンティティ格納位置管理
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _ENTITY_LOCATOR_H_
#define _ENTITY_LOCATOR_H_

#include <cstdint>
#include <unordered_map>

#include "ComponentDataChunk.h"

namespace HaraProject::Framework
{

/**
* @brief エンティティ格納位置管理
*/
class EntityLocator
{
public:
	/**
	* @brief エンティティの格納位置
	*/
	struct EntityLocation
	{
		/**
		* @brief 格納されているチャンクへのポインタ
		*/
		ComponentDataChunk* chunk;

		/**
		* @brief チャンク内でのインデックス
		*/
		uint32_t indexInChunk;
	};

	/**
	* @brief 格納位置登録
	* @param[in] id エンティティID
	* @param[in] chunk チャンクへのポインタ
	* @param[in] indexInChunk チャンク内のインデックス
	*/
	void RegisterLocation(uint32_t id, ComponentDataChunk* chunk, uint32_t indexInChunk);

	/**
	* @brief 格納位置登録
	* @param[in] id エンティティID
	*/
	EntityLocation GetLocation(uint32_t id);

private:
	/**
	* @brief エンティティIDと格納位置のマップ
	*/
	std::unordered_map<uint32_t, EntityLocation> m_id_to_location;
};

}// !namespace HaraProject::Framework

#endif // !_ENTITY_LOCATOR_H_
