#include <cstdint>
#include <vector>
#include <string>

#include "EditDataUtil.h"
#include "ComponentDataManager.h"
#include "ComponentDataChunk.h"

namespace HaraProject::Framework {

/**
* @brief �R���X�g���N�^
*/
ComponentDataManager::ComponentDataManager()
	: m_entity_version_checker(nullptr)
{
}

/**
* @brief �f�X�g���N�^
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
* @brief �G���e�B�e�B�ɃR���|�[�l���g�f�[�^��ǉ�
* @param[in] id �G���e�B�e�BID
* @param[in] newVersion �ړ���̃`�����N�Ŏg���o�[�W����
* @param[in] chunk �`�����N�ւ̃|�C���^
* @param[in] indexInChunk �`�����N���̃C���f�b�N�X
* @param[in] bit �R���|�[�l���g���ʃr�b�g
*/
ComponentDataChunk* ComponentDataManager::AddComponentData(uint32_t id, uint32_t newVersion, ComponentDataChunk* chunk, uint32_t indexInChunk, ComponentBits bit)
{
	// ���݂̃f�[�^���擾
	std::unordered_map<ComponentBits, ComponentDataBase*> entity_value_handler = chunk->GetEntityData(indexInChunk);

	// �ǉ�����R���|�[�l���g���n���h���ɒǉ�
	if (!entity_value_handler.contains(bit))
	{
		entity_value_handler.emplace(bit, ComponentRegistry::Constructor(bit));
	}

	// �ǉ���̃f�[�^��K�؂ȃ`�����N�֔z�u
	ComponentDataChunk* located_chunk = InsertComponentDataToChunk(id, newVersion, entity_value_handler);
	ReleaceEntityValueHandler(entity_value_handler);

	// �ړ����̃`�����N�̃o�[�W�����`�F�b�N�t���O��������
	chunk->SetNeedsVersionCheck(true);

	return located_chunk;
}

/**
* @brief �G���e�B�e�B����R���|�[�l���g���폜
* @param[in] id �G���e�B�e�BID
* @param[in] newVersion �ړ���̃`�����N�Ŏg���o�[�W����
* @param[in] chunk �`�����N�ւ̃|�C���^
* @param[in] indexInChunk �`�����N���̃C���f�b�N�X
* @param[in] bit �R���|�[�l���g���ʃr�b�g
*/
ComponentDataChunk* ComponentDataManager::RemoveComponentData(uint32_t id, uint32_t newVersion, ComponentDataChunk* chunk, uint32_t indexInChunk, ComponentBits bit)
{
	// ���݂̃f�[�^���擾
	std::unordered_map<ComponentBits, ComponentDataBase*> entity_value_handler = chunk->GetEntityData(indexInChunk);

	// �폜����R���|�[�l���g���n���h���ɂ��珜�O
	std::erase_if(entity_value_handler, [bit](auto& itr) { return itr.first == bit; });

	// ���O��̃f�[�^��K�؂ȃ`�����N�֔z�u
	ComponentDataChunk* located_chunk = InsertComponentDataToChunk(id, newVersion, entity_value_handler);
	ReleaceEntityValueHandler(entity_value_handler);

	// �ړ����̃`�����N�̃o�[�W�����`�F�b�N�t���O��������
	chunk->SetNeedsVersionCheck(true);

	// �g�p�����n���h�������
	ReleaceEntityValueHandler(entity_value_handler);

	return located_chunk;
}

/**
* @brief �G���e�B�e�B���i�[
* @param[in] id �G���e�B�e�BID
* @param[in] version �o�[�W����
* @param[in] entityValueHandler �l���i�[���ꂽ�G���e�B�e�B�̃f�[�^
*/
ComponentDataChunk* ComponentDataManager::InsertComponentDataToChunk(uint32_t id, uint32_t version, std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler)
{
	// �R���|�[�l���g�̑g�ݍ��킹�ɉ������}�X�N���쐬
	ComponentBits mask = GetMaskByEntityValueHandler(entityValueHandler);

	// ���p�ł���`�����N������΂����֒ǉ�
	ComponentDataChunk* chunk = FindChunkForComponents(mask);
	if (chunk != nullptr)
	{
		chunk->AllocateEntityToBuffer(id, version, entityValueHandler);
		return chunk;
	}

	// �V�K�̃`�����N���쐬���i�[
	m_bit_to_chunks[mask].push_back(new ComponentDataChunk(mask, m_entity_version_checker));
	m_bit_to_chunks[mask].back()->AllocateEntityToBuffer(id, version, entityValueHandler);
	return m_bit_to_chunks[mask].back();
}

/**
* @brief �G���e�B�e�B�o�[�W�����`�F�b�N�p�̃C���^�t�F�[�X��ݒ�
* @param[in] entityVersionChecker �G���e�B�e�B�o�[�W�����`�F�b�N�p�̃C���^�t�F�[�X�̃|�C���^
*/
void ComponentDataManager::SetEntityVersionChecker(IEntityVersionChecker* entityVersionChecker)
{
	m_entity_version_checker = entityVersionChecker;
}

/**
* @brief �w��̑g�̃R���|�[�l���g�f�[�^����舵���`�����N���擾
* @param[in] mask �R���|�[�l���g���ʃr�b�g
*/
std::vector<ComponentDataChunk*> ComponentDataManager::FindChunks(ComponentBits mask)
{
	std::vector<ComponentDataChunk*> result_chunks{};
	for (auto& chunks : m_bit_to_chunks)
	{
		// �w��̃r�b�g�����ׂė����Ă���Ό��ʂɒǉ�
		if ((chunks.first & mask) == mask)
		{
			result_chunks.insert(result_chunks.end(), 
				chunks.second.begin(), chunks.second.end());
		}
	}
	return result_chunks;
}

/**
* @brief �`�����N���̃G���e�B�e�B�̃o�[�W�����`�F�b�N���s��
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
* @brief �w��̑g�ŋ󂫂̂���`�����N���擾
* @param[in] mask �R���|�[�l���g�̑g������\���}�X�N
*/
ComponentDataChunk* ComponentDataManager::FindChunkForComponents(ComponentBits mask)
{
	// �w��̑g�ݍ��킹�������`�����N�����邩
	if (m_bit_to_chunks.contains(mask))
	{
		for (const auto& chunk : m_bit_to_chunks[mask])
		{
			// �i�[���ɋ󂫂�����Η��p�ł���`�����N�Ƃ��ĕԂ�
			if (!chunk->IsFull())
			{
				return chunk;
			}
		}
	}
	return nullptr;
}

/**
* @brief �n���h���Ɋ܂܂ꂽ�R���|�[�l���g�̑g�݂ɉ��������ʃr�b�g���擾
* @param[in] entityValueHandler �l���i�[���ꂽ�G���e�B�e�B�̃f�[�^
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