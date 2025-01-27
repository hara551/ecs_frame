#include <cstdint>
#include <memory>
#include <string>
#include <functional>

#include "ComponentRegistry.h"
#include "ComponentDataChunk.h"
#include "ComponentMask.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
* @param[in] mask コンポーネントの組合せを表すマスク
* @param[in] entityVersionChecker エンティティバージョンチェック用のインタフェース
*/
ComponentDataChunk::ComponentDataChunk(ComponentBits mask, IEntityVersionChecker* entityVersionChecker)
	: m_buffer(std::make_unique<std::byte[]>(BUFFER_SIZE))
	, m_num_entities(0)
	, m_max_entities_capacity(0)
	, m_needs_version_check(false)
	, m_entity_version_checker(entityVersionChecker)
{
	// マスクから、それぞれのコンポーネントのサイズを割り出す
	std::unordered_map<ComponentBits, size_t> bit_to_component_size;
	for (int i = 0; i < mask.size(); ++i)
	{
		if (mask[i])
		{
			ComponentBits bit{};
			bit.set(i);
			bit_to_component_size[bit] = ComponentRegistry::GetSize(bit);
		}
	}
	m_bit_to_component_size = bit_to_component_size;

	// エンティティを１つ格納するのに必要なサイズを算出
	size_t single_entity_size = sizeof(uint32_t) * MAX_TYPE_ENTITY_BLOCK;
	for (const auto& component : bit_to_component_size)
	{
		single_entity_size += component.second;
	}
	// 格納できるエンティティ数を割り出す
	m_max_entities_capacity = BUFFER_SIZE / single_entity_size;

	// --- サイズを考慮した配列をバッファに作成する
	// ID用配列作成
	new (m_buffer.get()) uint32_t[m_max_entities_capacity];
	size_t offset = sizeof(uint32_t) * m_max_entities_capacity;
	// バージョン用配列作成
	new (m_buffer.get() + offset) uint32_t[m_max_entities_capacity];
	offset += offset;
	// コンポーネントごとに配列作成
	for (const auto& component : bit_to_component_size)
	{
		std::byte* head_pointer = m_buffer.get() + offset;
		ComponentRegistry::PlacementNewArray(component.first, head_pointer, m_max_entities_capacity);

		// 配列の先頭ポインタを登録
		m_bit_to_head_pointer[component.first] = head_pointer;

		// 作成した配列サイズ分オフセットに加算
		offset += component.second * m_max_entities_capacity;
	}
}

/**
* @brief バッファにコンポーネントデータを配置
* @param[in] id エンティティID
* @param[in] version バージョン
* @param[in] entityValueHandler 値が格納されたエンティティのデータ
*/
void ComponentDataChunk::AllocateEntityToBuffer(uint32_t id, uint32_t version, std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler)
{
	// 使えるスロットのインデックスを取得
	uint32_t index = AssignUsableIndex();

	// IDとバージョンを格納
	uint32_t* id_array = CalculateEntityBlockArrayHead(EntityBlockType::Id);
	id_array[index] = id;
	uint32_t* version_array = CalculateEntityBlockArrayHead(EntityBlockType::Version);
	version_array[index] = version;

	for (const auto& component : entityValueHandler)
	{
		// コンポーネントごとに値を配列に格納
		ComponentBits bit = component.first;
		std::byte* buffer = m_bit_to_head_pointer[bit] + m_bit_to_component_size[bit] * index;
		ComponentRegistry::AllocateInstance(
			bit,				// 識別bit
			buffer,				// 値を格納するバッファ
			component.second	// 値が入ったComponentDataBaseポインタ
		);
	}
	++m_num_entities;
}

/**
* @brief 値を保持したエンティティのデータを取得
* @param[in] index インデックス
*/
std::unordered_map<ComponentBits, ComponentDataBase*> ComponentDataChunk::GetEntityData(uint32_t index)
{
	std::unordered_map<ComponentBits, ComponentDataBase*> entity_value_handler{};
	for (const auto& component : m_bit_to_head_pointer)
	{
		ComponentBits bit = component.first;
		ComponentDataBase* component_data = CalculateComponentDataPointer(bit, index);
		entity_value_handler.emplace(bit, ComponentRegistry::CopyConstructor(bit, component_data));
	}
	return entity_value_handler;
}

/**
* @brief 使えるスロットのインデックスを取得
*/
uint32_t ComponentDataChunk::AssignUsableIndex()
{
	// 空きインデックスがあれば再利用
	if (!m_free_slot_indicies.empty())
	{
		uint32_t index = m_free_slot_indicies.front();
		m_free_slot_indicies.erase(m_free_slot_indicies.begin());
		return index;
	}
	// 無ければ最後尾
	return m_num_entities;
}

/**
* @brief インデックスからIDを取得
* @param[in] index インデックス
*/
uint32_t ComponentDataChunk::GetIdByIndex(uint32_t index)
{
	if (m_num_entities - 1 >= index)
	{
		uint32_t* id_array = CalculateEntityBlockArrayHead(EntityBlockType::Id);
		return id_array[index];
	}
	return 0;
}

/**
* @brief インデックスからバージョンを取得
* @param[in] index インデックス
*/
uint32_t ComponentDataChunk::GetVersionByIndex(uint32_t index)
{
	if (m_num_entities - 1 >= index)
	{
		uint32_t* version_array = CalculateEntityBlockArrayHead(EntityBlockType::Version);
		return version_array[index];
	}
	return 0;
}

/**
* @brief バッファが満杯か
*/
bool ComponentDataChunk::IsFull()
{
	return m_max_entities_capacity <= m_num_entities;
}

/**
* @brief エンティティIDからインデックスを取得
* @param[in] id エンティティID
*/
uint32_t ComponentDataChunk::GetIndex(uint32_t id)
{
	uint32_t* id_array = CalculateEntityBlockArrayHead(EntityBlockType::Id);
	for (int i = 0; i < m_num_entities; ++i)
	{
		if (id_array[i] == id)
		{
			return i;
		}
	}
	return 0;
}

/**
* @brief 特定のエンティティのコンポーネントデータを無効化
* @param[in] indicies チャンク内のインデックス
*/
void ComponentDataChunk::DisableEntityData(std::vector<uint32_t> indicies)
{
	for (auto& index : indicies)
	{
		// コンポーネントごとに無効化していく
		for (const auto& component : m_bit_to_head_pointer)
		{
			ComponentDataBase* component_data = CalculateComponentDataPointer(component.first, index);
			component_data->Disable();
		}

		// 空きスロットとして記録
		m_free_slot_indicies.push_back(index);
	}
}

/**
* @brief チャンク内エンティティのバージョンをチェック
*/
void ComponentDataChunk::CheckEntitiesVersion()
{
	uint32_t* id_array = CalculateEntityBlockArrayHead(EntityBlockType::Id);
	uint32_t* version_array = CalculateEntityBlockArrayHead(EntityBlockType::Version);

	std::vector<uint32_t> old_entity_indicies{};
	for (int index = 0; index < m_num_entities; ++index)
	{
		// 古いバージョンのものを無効とする
		if (!m_entity_version_checker->IsValidEntity(id_array[index], version_array[index]))
		{
			old_entity_indicies.push_back(index);
		}
	}
	// データを無効化
	DisableEntityData(old_entity_indicies);
}

/**
* @brief バージョンチェック要求フラグを設定
* @param[in] needsFlag フラグ
*/
void ComponentDataChunk::SetNeedsVersionCheck(bool needsFlag)
{
	m_needs_version_check = needsFlag;
}

/**
* @brief バージョンチェックを必要としているか
*/
bool ComponentDataChunk::NeedsVersionCheck()
{
	return false;
}

/**
* @brief 格納されているエンティティの数を取得
*/
uint32_t ComponentDataChunk::GetNumEntities()
{
	return m_num_entities;
}

/**
* @brief エンティティID配列の先頭ポインタを取得
* @param[in] entityBlockType エンティティ情報の種類
*/
uint32_t* ComponentDataChunk::CalculateEntityBlockArrayHead(EntityBlockType entityBlockType)
{
	uint32_t* array_head{};
	switch (entityBlockType)
	{
	case Id:
		array_head = reinterpret_cast<uint32_t*>(m_buffer.get());
		break;
	case Version:
		array_head = reinterpret_cast<uint32_t*>(m_buffer.get() + sizeof(uint32_t) * m_max_entities_capacity);
		break;
	}
	return array_head;
}

/**
* @brief 指定のコンポーネントデータのポインタを取得
* @param[in] bit コンポーネントデータ識別ビット
* @param[in] index インデックス
*/
ComponentDataBase* ComponentDataChunk::CalculateComponentDataPointer(ComponentBits bit, uint32_t index)
{
	if (m_bit_to_head_pointer.contains(bit) && m_bit_to_component_size.contains(bit))
	{
		ComponentDataBase* component = reinterpret_cast<ComponentDataBase*>(m_bit_to_head_pointer[bit]);

		return reinterpret_cast<ComponentDataBase*>(m_bit_to_head_pointer[bit] + m_bit_to_component_size[bit] * index);
	}
	return nullptr;
}

}// !namespace HaraProject::Framework