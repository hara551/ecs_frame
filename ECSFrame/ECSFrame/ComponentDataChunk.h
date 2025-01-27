/**
* @file   ComponentDataChunk.h
* @brief  同じ組のコンポーネントを持つエンティティのデータ管理クラス定義.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _COMPONENT_DATA_CHUNK_H_
#define _COMPONENT_DATA_CHUNK_H_

#include <memory>
#include <cstdint>
#include <unordered_map>

#include "ComponentMask.h"
#include "ComponentRegistry.h"
#include "ComponentDataBase.h"
#include "EntityValueHandler.h"
#include "IEntityVersionChecker.h"

namespace HaraProject::Framework {

class ComponentDataChunk
{
public:
	/**
	* @brief バッファに格納するエンティティについての情報分類
	*/
	enum EntityBlockType
	{
		Id,
		Version,
		MAX_TYPE_ENTITY_BLOCK
	};

	/**
	* @brief 確保するバッファの単位サイズ
	*/
	static constexpr size_t BUFFER_SIZE = 4096;

	/**
	* @brief コンストラクタ
	* @param[in] mask コンポーネントの組合せを表すマスク
	* @param[in] entityVersionChecker エンティティバージョンチェック用のインタフェース
	*/
	ComponentDataChunk(ComponentBits mask, IEntityVersionChecker* entityVersionChecker);

	/**
	* @brief バッファにコンポーネントデータを配置
	* @param[in] id エンティティID
	* @param[in] version バージョン
	* @param[in] entityValueHandler 値が格納されたエンティティのデータ
	*/
	void AllocateEntityToBuffer(uint32_t id, uint32_t version, std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler);

	/**
	* @brief 値を保持したエンティティのデータを取得
	* @param[in] index インデックス
	*/
	std::unordered_map<ComponentBits, ComponentDataBase*> GetEntityData(uint32_t index);

	/**
	* @brief 使えるスロットのインデックスを取得
	*/
	uint32_t AssignUsableIndex();

	/**
	* @brief インデックスからIDを取得
	* @param[in] index インデックス
	*/
	uint32_t GetIdByIndex(uint32_t index);

	/**
	* @brief インデックスからバージョンを取得
	* @param[in] index インデックス
	*/
	uint32_t GetVersionByIndex(uint32_t index);

	/**
	* @brief バッファが満杯か
	*/
	bool IsFull();

	/**
	* @brief エンティティIDからインデックスを取得
	* @param[in] id エンティティID
	*/
	uint32_t GetIndex(uint32_t id);

	/**
	* @brief 格納されているエンティティの数を取得
	*/
	uint32_t GetNumEntities();

	/**
	* @brief 特定のエンティティのコンポーネントデータを無効化
	* @param[in] indicies チャンク内のインデックス
	*/
	void DisableEntityData(std::vector<uint32_t> indicies);

	/**
	* @brief チャンク内エンティティのバージョンをチェック
	*/
	void CheckEntitiesVersion();

	/**
	* @brief バージョンチェック要求フラグを設定
	* @param[in] needsFlag フラグ
	*/
	void SetNeedsVersionCheck(bool needsFlag);

	/**
	* @brief バージョンチェックを必要としているか
	*/
	bool NeedsVersionCheck();

	/**
	* @brief エンティティ情報配列の先頭ポインタを取得
	* @param[in] entityBlockType エンティティ情報の種類
	*/
	uint32_t* CalculateEntityBlockArrayHead(EntityBlockType entityBlockType);

	/**
	* @brief 指定のコンポーネントデータのポインタを取得
	* @param[in] bit コンポーネントデータ識別ビット
	* @param[in] index インデックス
	*/
	ComponentDataBase* CalculateComponentDataPointer(ComponentBits bit, uint32_t index);


private:
	/**
	* @brief データを格納するバッファ
	*/
	std::unique_ptr<std::byte[]> m_buffer;

	/**
	* @brief コンポーネントごとの先頭ポインタ
	*/
	std::unordered_map<ComponentBits, std::byte*> m_bit_to_head_pointer;

	/**
	* @brief コンポーネントごとのサイズ
	*/
	std::unordered_map<ComponentBits, size_t> m_bit_to_component_size;

	/**
	* @brief 格納できるエンティティの最大数
	*/
	uint32_t m_max_entities_capacity;

	/**
	* @brief 格納されているエンティティ数
	*/
	uint32_t m_num_entities;

	/**
	* @brief 削除や移動が起きた時にバージョンチェックを求めるフラグ
	*/
	bool m_needs_version_check;

	/**
	* @brief 空いているインデックスのリスト
	*/
	std::vector<uint32_t> m_free_slot_indicies;

	/**
	* @brief エンティティバージョンチェック用のインタフェース
	*/
	IEntityVersionChecker* m_entity_version_checker;
};

}// !namespace HaraProject::Framework

#endif // !_COMPONENT_DATA_CHUNK_H_
