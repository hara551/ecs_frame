/**
* @file   IComponentDataManager.h
* @brief  コンポーネントデータ操作インターフェース.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _ICOMPONENT_DATA_MANAGER_H_
#define _ICOMPONENT_DATA_MANAGER_H_

#include <cstdint>

#include "ComponentMask.h"
#include "ComponentDataChunk.h"
#include "EntityValueHandler.h"
#include "IEntityVersionChecker.h"

namespace HaraProject::Framework
{

/**
* @brief　コンポーネントデータ操作インターフェース
*/
class IComponentDataManager
{
public:
	/**
	* @brief デストラクタ
	*/
	virtual ~IComponentDataManager() = default;

	/**
	* @brief エンティティにコンポーネントデータを追加
	* @param[in] id エンティティID
	* @param[in] newVersion 移動先のチャンクで使うバージョン
	* @param[in] chunk チャンクへのポインタ
	* @param[in] indexInChunk チャンク内のインデックス
	* @param[in] bit コンポーネント識別ビット
	*/
	virtual ComponentDataChunk* AddComponentData(uint32_t id, uint32_t newVersion, ComponentDataChunk* chunk, uint32_t indexInChunk, ComponentBits bit) = 0;
	
	/**
	* @brief エンティティからコンポーネントを削除
	* @param[in] id エンティティID
	* @param[in] newVersion 移動先のチャンクで使うバージョン
	* @param[in] chunk チャンクへのポインタ
	* @param[in] indexInChunk チャンク内のインデックス
	* @param[in] bit コンポーネント識別ビット
	*/
	virtual ComponentDataChunk* RemoveComponentData(uint32_t id, uint32_t newVersion, ComponentDataChunk* chunk, uint32_t indexInChunk, ComponentBits bit) = 0;

	/**
	* @brief エンティティを格納
	* @param[in] id エンティティID
	* @param[in] version バージョン
	* @param[in] entityValueHandler 値が格納されたエンティティのデータ
	* @return エンティティを格納したチャンクのポインタ
	*/
	virtual ComponentDataChunk* InsertComponentDataToChunk(uint32_t id, uint32_t version, std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler) = 0;

	/**
	* @brief エンティティバージョンチェック用のインタフェースを設定
	* @param[in] entityVersionChecker エンティティバージョンチェック用のインタフェースのポインタ
	*/
	virtual void SetEntityVersionChecker(IEntityVersionChecker* entityVersionChecker) = 0;
};

}// !namespace HaraProject::Framework

#endif // !_ICOMPONENT_DATA_MANAGER_H_