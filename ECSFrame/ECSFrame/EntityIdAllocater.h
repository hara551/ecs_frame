/**
* @file   EntityIdAllocater.h
* @brief  エンティティID管理クラス定義.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _ENTITY_ID_ALLOCATER_H_
#define _ENTITY_ID_ALLOCATER_H_

#include <cstdint>
#include <vector>

namespace HaraProject::Framework
{

/**
* @brief エンティティID割り当て
*/
class EntityIdAllocater
{
public:
	/**
	* @brief エンティティ識別情報
	*/
	struct EntityHandle
	{
		/**
		* @brief エンティティID
		*/
		uint32_t id;

		/**
		* @brief バージョン
		*/
		uint32_t version;
	};

	/**
	* @brief コンストラクタ
	*/
	EntityIdAllocater();

	/**
	* @brief エンティティIDを空ける
	* @param[in] id エンティティID
	*/
	void FreeUpId(uint32_t id);

	/**
	* @brief 使えるIDを割り当てる
	*/
	EntityHandle AssignUsableId();

	/**
	* @brief 新しくIDを発行する
	*/
	EntityHandle IssueNewId();

	/**
	* @brief IDが有効か
	* @param[in] id エンティティID
	* @param[in] version バージョン
	*/
	bool IsValidId(uint32_t id, uint32_t version);

	/**
	* @brief 有効とするバージョンを上げる
	* @param[in] エンティティID
	*/
	uint32_t IncreaceValidVersion(uint32_t id);

	/**
	* @brief 次に割り当てるID
	*/
	uint32_t m_next_id;

	/**
	* @brief エンティティの最新バージョン
	* @attention インデックスをIDとしたときのバージョン
	*/
	std::vector<uint32_t> m_latest_versions;

	/**
	* @brief 空きIDリスト
	*/
	std::vector<uint32_t>m_free_ids;
};

}// !namespace HaraProject::Framework

#endif // !_ENTITY_ID_ALLOCATER_H_
