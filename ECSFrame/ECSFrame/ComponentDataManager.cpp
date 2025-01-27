#include <cstdint>
#include <vector>
#include <string>

#include "EditDataUtil.h"
#include "ComponentDataManager.h"
#include "ComponentDataChunk.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
ComponentDataManager::ComponentDataManager()
	: m_entity_version_checker(nullptr)
{
}

/**
* @brief デストラクタ
*/
ComponentDataManager::~ComponentDataManager()
{
	for (auto& chunks : m_bit_to_chunks)
	{
		for (auto& chunk : chunks.second)
		{
			if (chunk != nullptr)
			{
				delete chunk;
				chunk = nullptr;
			}
		}
	}
}

/**
* @brief エンティティにコンポーネントデータを追加
* @param[in] id エンティティID
* @param[in] newVersion 移動先のチャンクで使うバージョン
* @param[in] chunk チャンクへのポインタ
* @param[in] indexInChunk チャンク内のインデックス
* @param[in] bit コンポーネント識別ビット
*/
ComponentDataChunk* ComponentDataManager::AddComponentData(uint32_t id, uint32_t newVersion, ComponentDataChunk* chunk, uint32_t indexInChunk, ComponentBits bit)
{
	// 現在のデータを取得
	std::unordered_map<ComponentBits, ComponentDataBase*> entity_value_handler = chunk->GetEntityData(indexInChunk);

	// 追加するコンポーネントもハンドルに追加
	if (!entity_value_handler.contains(bit))
	{
		entity_value_handler.emplace(bit, ComponentRegistry::Constructor(bit));
	}

	// 追加後のデータを適切なチャンクへ配置
	ComponentDataChunk* located_chunk = InsertComponentDataToChunk(id, newVersion, entity_value_handler);
	ReleaceEntityValueHandler(entity_value_handler);

	// 移動元のチャンクのバージョンチェックフラグを挙げる
	chunk->SetNeedsVersionCheck(true);

	return located_chunk;
}

/**
* @brief エンティティからコンポーネントを削除
* @param[in] id エンティティID
* @param[in] newVersion 移動先のチャンクで使うバージョン
* @param[in] chunk チャンクへのポインタ
* @param[in] indexInChunk チャンク内のインデックス
* @param[in] bit コンポーネント識別ビット
*/
ComponentDataChunk* ComponentDataManager::RemoveComponentData(uint32_t id, uint32_t newVersion, ComponentDataChunk* chunk, uint32_t indexInChunk, ComponentBits bit)
{
	// 現在のデータを取得
	std::unordered_map<ComponentBits, ComponentDataBase*> entity_value_handler = chunk->GetEntityData(indexInChunk);

	// 削除するコンポーネントをハンドルにから除外
	std::erase_if(entity_value_handler, [bit](auto& itr) { return itr.first == bit; });

	// 除外後のデータを適切なチャンクへ配置
	ComponentDataChunk* located_chunk = InsertComponentDataToChunk(id, newVersion, entity_value_handler);
	ReleaceEntityValueHandler(entity_value_handler);

	// 移動元のチャンクのバージョンチェックフラグを挙げる
	chunk->SetNeedsVersionCheck(true);

	// 使用したハンドルを解放
	ReleaceEntityValueHandler(entity_value_handler);

	return located_chunk;
}

/**
* @brief エンティティを格納
* @param[in] id エンティティID
* @param[in] version バージョン
* @param[in] entityValueHandler 値が格納されたエンティティのデータ
*/
ComponentDataChunk* ComponentDataManager::InsertComponentDataToChunk(uint32_t id, uint32_t version, std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler)
{
	// コンポーネントの組み合わせに応じたマスクを作成
	ComponentBits mask = GetMaskByEntityValueHandler(entityValueHandler);

	// 利用できるチャンクがあればそこへ追加
	ComponentDataChunk* chunk = FindChunkForComponents(mask);
	if (chunk != nullptr)
	{
		chunk->AllocateEntityToBuffer(id, version, entityValueHandler);
		return chunk;
	}

	// 新規のチャンクを作成し格納
	m_bit_to_chunks[mask].push_back(new ComponentDataChunk(mask, m_entity_version_checker));
	m_bit_to_chunks[mask].back()->AllocateEntityToBuffer(id, version, entityValueHandler);
	return m_bit_to_chunks[mask].back();
}

/**
* @brief エンティティバージョンチェック用のインタフェースを設定
* @param[in] entityVersionChecker エンティティバージョンチェック用のインタフェースのポインタ
*/
void ComponentDataManager::SetEntityVersionChecker(IEntityVersionChecker* entityVersionChecker)
{
	m_entity_version_checker = entityVersionChecker;
}

/**
* @brief 指定の組のコンポーネントデータを取り扱うチャンクを取得
* @param[in] mask コンポーネント識別ビット
*/
std::vector<ComponentDataChunk*> ComponentDataManager::FindChunks(ComponentBits mask)
{
	std::vector<ComponentDataChunk*> result_chunks{};
	for (auto& chunks : m_bit_to_chunks)
	{
		// 指定のビットがすべて立っていれば結果に追加
		if ((chunks.first & mask) == mask)
		{
			result_chunks.insert(result_chunks.end(), 
				chunks.second.begin(), chunks.second.end());
		}
	}
	return result_chunks;
}

/**
* @brief チャンク内のエンティティのバージョンチェックを行う
*/
void ComponentDataManager::CheckChunkEntitiesVersion()
{
	for (auto& [bit, chunks] : m_bit_to_chunks)
	{
		for (auto& chunk : chunks)
		{
			if (chunk->NeedsVersionCheck())
			{
				chunk->CheckEntitiesVersion(); 
			}
		}
	}
}

/**
* @brief 指定の組で空きのあるチャンクを取得
* @param[in] mask コンポーネントの組合せを表すマスク
*/
ComponentDataChunk* ComponentDataManager::FindChunkForComponents(ComponentBits mask)
{
	// 指定の組み合わせを扱うチャンクがあるか
	if (m_bit_to_chunks.contains(mask))
	{
		for (const auto& chunk : m_bit_to_chunks[mask])
		{
			// 格納数に空きがあれば利用できるチャンクとして返す
			if (!chunk->IsFull())
			{
				return chunk;
			}
		}
	}
	return nullptr;
}

/**
* @brief ハンドルに含まれたコンポーネントの組みに応じた識別ビットを取得
* @param[in] entityValueHandler 値が格納されたエンティティのデータ
*/
ComponentBits ComponentDataManager::GetMaskByEntityValueHandler(const std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler)
{
	ComponentBits mask{};
	for (const auto& component : entityValueHandler)
	{
		mask |= component.first;
	}
	return mask;
}

}// namespace HaraProject::Framework