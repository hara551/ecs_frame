/**
* @file   ComponentDataManager.h
* @brief  コンポーネントデータ管理クラス定義.
* @author Hara Sota.
* @date   2024/10/07
*/
#ifndef _COMPONENT_DATA_MANAGER_H_
#define _COMPONENT_DATA_MANAGER_H_

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "ComponentDataChunk.h"
#include "ComponentDataBase.h"
#include "EntityValueHandler.h"
#include "ComponentRegistry.h"
#include "ComponentMask.h"
#include "IEntityVersionChecker.h"

#include "IComponentDataManager.h"
#include "IChunkProvider.h"

namespace HaraProject::Framework {

/**
* @brief コンポーネントデータ管理クラス
*/
class ComponentDataManager : public IComponentDataManager, public IChunkProvider
{
public:
	/**
	* @brief コンストラクタ
	*/
	ComponentDataManager();

	/**
	* @brief デストラクタ
	*/
	~ComponentDataManager();

	/**
	* @brief エンティティにコンポーネントデータを追加
	* @param[in] id エンティティID
	* @param[in] newVersion 移動先のチャンクで使うバージョン
	* @param[in] chunk チャンクへのポインタ
	* @param[in] indexInChunk チャンク内のインデックス
	* @param[in] bit コンポーネント識別ビット
	*/
	ComponentDataChunk* AddComponentData(uint32_t id, uint32_t newVersion, ComponentDataChunk* chunk, uint32_t indexInChunk, ComponentBits bit)override;

	/**
	* @brief エンティティからコンポーネントを削除
	* @param[in] id エンティティID
	* @param[in] newVersion 移動先のチャンクで使うバージョン
	* @param[in] chunk チャンクへのポインタ
	* @param[in] indexInChunk チャンク内のインデックス
	* @param[in] bit コンポーネント識別ビット
	*/
	ComponentDataChunk* RemoveComponentData(uint32_t id, uint32_t newVersion, ComponentDataChunk* chunk, uint32_t indexInChunk, ComponentBits bit)override;

	/**
	* @brief エンティティを格納
	* @param[in] id エンティティID
	* @param[in] version バージョン
	* @param[in] entityValueHandler 値が格納されたエンティティのデータ
	* @return エンティティを格納したチャンクのポインタ
	*/
	ComponentDataChunk* InsertComponentDataToChunk(uint32_t id, uint32_t version, std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler)override;

	/**
	* @brief エンティティバージョンチェック用のインタフェースを設定
	* @param[in] entityVersionChecker エンティティバージョンチェック用のインタフェースのポインタ
	*/
	void SetEntityVersionChecker(IEntityVersionChecker* entityVersionChecker)override;

	/**
	* @brief 指定の組のコンポーネントデータを取り扱うチャンクを取得
	* @param[in] mask コンポーネント識別ビット
	*/
	std::vector<ComponentDataChunk*> FindChunks(ComponentBits mask)override;

	/**
	* @brief チャンク内のエンティティのバージョンチェックを行う
	*/
	void CheckChunkEntitiesVersion();

private:
	/**
	* @brief 指定の組で空きのあるチャンクを取得
	* @param[in] mask コンポーネントの組合せを表すマスク
	*/
	ComponentDataChunk* FindChunkForComponents(ComponentBits mask);

	/**
	* @brief ハンドルに含まれたコンポーネントの組みに応じた識別ビットを取得
	* @param[in] entityValueHandler 値が格納されたエンティティのデータ
	*/
	ComponentBits GetMaskByEntityValueHandler(const std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler);

	/**
	* @brief コンポーネント組み合わせの識別ビットとチャンクのマップ
	*/
	std::unordered_map <ComponentBits, std::vector <ComponentDataChunk*>> m_bit_to_chunks;

	/**
	* @brief エンティティバージョンチェック用のインタフェース
	*/
	IEntityVersionChecker* m_entity_version_checker;
};

}// namespace HaraProject::Framework

#endif // !_COMPONENT_DATA_MANAGER_H_