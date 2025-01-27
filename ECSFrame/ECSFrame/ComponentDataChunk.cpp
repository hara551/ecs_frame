#include <cstdint>
#include <memory>
#include <string>
#include <functional>

#include "ComponentRegistry.h"
#include "ComponentDataChunk.h"
#include "ComponentMask.h"

namespace HaraProject::Framework {

/**
* @brief �R���X�g���N�^
* @param[in] mask �R���|�[�l���g�̑g������\���}�X�N
* @param[in] entityVersionChecker �G���e�B�e�B�o�[�W�����`�F�b�N�p�̃C���^�t�F�[�X
*/
ComponentDataChunk::ComponentDataChunk(ComponentBits mask, IEntityVersionChecker* entityVersionChecker)
	: m_buffer(std::make_unique<std::byte[]>(BUFFER_SIZE))
	, m_num_entities(0)
	, m_max_entities_capacity(0)
	, m_needs_version_check(false)
	, m_entity_version_checker(entityVersionChecker)
{
	// �}�X�N����A���ꂼ��̃R���|�[�l���g�̃T�C�Y������o��
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

	// �G���e�B�e�B���P�i�[����̂ɕK�v�ȃT�C�Y���Z�o
	size_t single_entity_size = sizeof(uint32_t) * MAX_TYPE_ENTITY_BLOCK;
	for (const auto& component : bit_to_component_size)
	{
		single_entity_size += component.second;
	}
	// �i�[�ł���G���e�B�e�B��������o��
	m_max_entities_capacity = BUFFER_SIZE / single_entity_size;

	// --- �T�C�Y���l�������z����o�b�t�@�ɍ쐬����
	// ID�p�z��쐬
	new (m_buffer.get()) uint32_t[m_max_entities_capacity];
	size_t offset = sizeof(uint32_t) * m_max_entities_capacity;
	// �o�[�W�����p�z��쐬
	new (m_buffer.get() + offset) uint32_t[m_max_entities_capacity];
	offset += offset;
	// �R���|�[�l���g���Ƃɔz��쐬
	for (const auto& component : bit_to_component_size)
	{
		std::byte* head_pointer = m_buffer.get() + offset;
		ComponentRegistry::PlacementNewArray(component.first, head_pointer, m_max_entities_capacity);

		// �z��̐擪�|�C���^��o�^
		m_bit_to_head_pointer[component.first] = head_pointer;

		// �쐬�����z��T�C�Y���I�t�Z�b�g�ɉ��Z
		offset += component.second * m_max_entities_capacity;
	}
}

/**
* @brief �o�b�t�@�ɃR���|�[�l���g�f�[�^��z�u
* @param[in] id �G���e�B�e�BID
* @param[in] version �o�[�W����
* @param[in] entityValueHandler �l���i�[���ꂽ�G���e�B�e�B�̃f�[�^
*/
void ComponentDataChunk::AllocateEntityToBuffer(uint32_t id, uint32_t version, std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler)
{
	// �g����X���b�g�̃C���f�b�N�X���擾
	uint32_t index = AssignUsableIndex();

	// ID�ƃo�[�W�������i�[
	uint32_t* id_array = CalculateEntityBlockArrayHead(EntityBlockType::Id);
	id_array[index] = id;
	uint32_t* version_array = CalculateEntityBlockArrayHead(EntityBlockType::Version);
	version_array[index] = version;

	for (const auto& component : entityValueHandler)
	{
		// �R���|�[�l���g���Ƃɒl��z��Ɋi�[
		ComponentBits bit = component.first;
		std::byte* buffer = m_bit_to_head_pointer[bit] + m_bit_to_component_size[bit] * index;
		ComponentRegistry::AllocateInstance(
			bit,				// ����bit
			buffer,				// �l���i�[����o�b�t�@
			component.second	// �l��������ComponentDataBase�|�C���^
		);
	}
	++m_num_entities;
}

/**
* @brief �l��ێ������G���e�B�e�B�̃f�[�^���擾
* @param[in] index �C���f�b�N�X
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
* @brief �g����X���b�g�̃C���f�b�N�X���擾
*/
uint32_t ComponentDataChunk::AssignUsableIndex()
{
	// �󂫃C���f�b�N�X������΍ė��p
	if (!m_free_slot_indicies.empty())
	{
		uint32_t index = m_free_slot_indicies.front();
		m_free_slot_indicies.erase(m_free_slot_indicies.begin());
		return index;
	}
	// ������΍Ō��
	return m_num_entities;
}

/**
* @brief �C���f�b�N�X����ID���擾
* @param[in] index �C���f�b�N�X
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
* @brief �C���f�b�N�X����o�[�W�������擾
* @param[in] index �C���f�b�N�X
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
* @brief �o�b�t�@�����t��
*/
bool ComponentDataChunk::IsFull()
{
	return m_max_entities_capacity <= m_num_entities;
}

/**
* @brief �G���e�B�e�BID����C���f�b�N�X���擾
* @param[in] id �G���e�B�e�BID
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
* @brief ����̃G���e�B�e�B�̃R���|�[�l���g�f�[�^�𖳌���
* @param[in] indicies �`�����N���̃C���f�b�N�X
*/
void ComponentDataChunk::DisableEntityData(std::vector<uint32_t> indicies)
{
	for (auto& index : indicies)
	{
		// �R���|�[�l���g���Ƃɖ��������Ă���
		for (const auto& component : m_bit_to_head_pointer)
		{
			ComponentDataBase* component_data = CalculateComponentDataPointer(component.first, index);
			component_data->Disable();
		}

		// �󂫃X���b�g�Ƃ��ċL�^
		m_free_slot_indicies.push_back(index);
	}
}

/**
* @brief �`�����N���G���e�B�e�B�̃o�[�W�������`�F�b�N
*/
void ComponentDataChunk::CheckEntitiesVersion()
{
	uint32_t* id_array = CalculateEntityBlockArrayHead(EntityBlockType::Id);
	uint32_t* version_array = CalculateEntityBlockArrayHead(EntityBlockType::Version);

	std::vector<uint32_t> old_entity_indicies{};
	for (int index = 0; index < m_num_entities; ++index)
	{
		// �Â��o�[�W�����̂��̂𖳌��Ƃ���
		if (!m_entity_version_checker->IsValidEntity(id_array[index], version_array[index]))
		{
			old_entity_indicies.push_back(index);
		}
	}
	// �f�[�^�𖳌���
	DisableEntityData(old_entity_indicies);
}

/**
* @brief �o�[�W�����`�F�b�N�v���t���O��ݒ�
* @param[in] needsFlag �t���O
*/
void ComponentDataChunk::SetNeedsVersionCheck(bool needsFlag)
{
	m_needs_version_check = needsFlag;
}

/**
* @brief �o�[�W�����`�F�b�N��K�v�Ƃ��Ă��邩
*/
bool ComponentDataChunk::NeedsVersionCheck()
{
	return false;
}

/**
* @brief �i�[����Ă���G���e�B�e�B�̐����擾
*/
uint32_t ComponentDataChunk::GetNumEntities()
{
	return m_num_entities;
}

/**
* @brief �G���e�B�e�BID�z��̐擪�|�C���^���擾
* @param[in] entityBlockType �G���e�B�e�B���̎��
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
* @brief �w��̃R���|�[�l���g�f�[�^�̃|�C���^���擾
* @param[in] bit �R���|�[�l���g�f�[�^���ʃr�b�g
* @param[in] index �C���f�b�N�X
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