/**
* @file   ComponentDataChunk.h
* @brief  �����g�̃R���|�[�l���g�����G���e�B�e�B�̃f�[�^�Ǘ��N���X��`.
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
	* @brief �o�b�t�@�Ɋi�[����G���e�B�e�B�ɂ��Ă̏�񕪗�
	*/
	enum EntityBlockType
	{
		Id,
		Version,
		MAX_TYPE_ENTITY_BLOCK
	};

	/**
	* @brief �m�ۂ���o�b�t�@�̒P�ʃT�C�Y
	*/
	static constexpr size_t BUFFER_SIZE = 4096;

	/**
	* @brief �R���X�g���N�^
	* @param[in] mask �R���|�[�l���g�̑g������\���}�X�N
	* @param[in] entityVersionChecker �G���e�B�e�B�o�[�W�����`�F�b�N�p�̃C���^�t�F�[�X
	*/
	ComponentDataChunk(ComponentBits mask, IEntityVersionChecker* entityVersionChecker);

	/**
	* @brief �o�b�t�@�ɃR���|�[�l���g�f�[�^��z�u
	* @param[in] id �G���e�B�e�BID
	* @param[in] version �o�[�W����
	* @param[in] entityValueHandler �l���i�[���ꂽ�G���e�B�e�B�̃f�[�^
	*/
	void AllocateEntityToBuffer(uint32_t id, uint32_t version, std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler);

	/**
	* @brief �l��ێ������G���e�B�e�B�̃f�[�^���擾
	* @param[in] index �C���f�b�N�X
	*/
	std::unordered_map<ComponentBits, ComponentDataBase*> GetEntityData(uint32_t index);

	/**
	* @brief �g����X���b�g�̃C���f�b�N�X���擾
	*/
	uint32_t AssignUsableIndex();

	/**
	* @brief �C���f�b�N�X����ID���擾
	* @param[in] index �C���f�b�N�X
	*/
	uint32_t GetIdByIndex(uint32_t index);

	/**
	* @brief �C���f�b�N�X����o�[�W�������擾
	* @param[in] index �C���f�b�N�X
	*/
	uint32_t GetVersionByIndex(uint32_t index);

	/**
	* @brief �o�b�t�@�����t��
	*/
	bool IsFull();

	/**
	* @brief �G���e�B�e�BID����C���f�b�N�X���擾
	* @param[in] id �G���e�B�e�BID
	*/
	uint32_t GetIndex(uint32_t id);

	/**
	* @brief �i�[����Ă���G���e�B�e�B�̐����擾
	*/
	uint32_t GetNumEntities();

	/**
	* @brief ����̃G���e�B�e�B�̃R���|�[�l���g�f�[�^�𖳌���
	* @param[in] indicies �`�����N���̃C���f�b�N�X
	*/
	void DisableEntityData(std::vector<uint32_t> indicies);

	/**
	* @brief �`�����N���G���e�B�e�B�̃o�[�W�������`�F�b�N
	*/
	void CheckEntitiesVersion();

	/**
	* @brief �o�[�W�����`�F�b�N�v���t���O��ݒ�
	* @param[in] needsFlag �t���O
	*/
	void SetNeedsVersionCheck(bool needsFlag);

	/**
	* @brief �o�[�W�����`�F�b�N��K�v�Ƃ��Ă��邩
	*/
	bool NeedsVersionCheck();

	/**
	* @brief �G���e�B�e�B���z��̐擪�|�C���^���擾
	* @param[in] entityBlockType �G���e�B�e�B���̎��
	*/
	uint32_t* CalculateEntityBlockArrayHead(EntityBlockType entityBlockType);

	/**
	* @brief �w��̃R���|�[�l���g�f�[�^�̃|�C���^���擾
	* @param[in] bit �R���|�[�l���g�f�[�^���ʃr�b�g
	* @param[in] index �C���f�b�N�X
	*/
	ComponentDataBase* CalculateComponentDataPointer(ComponentBits bit, uint32_t index);


private:
	/**
	* @brief �f�[�^���i�[����o�b�t�@
	*/
	std::unique_ptr<std::byte[]> m_buffer;

	/**
	* @brief �R���|�[�l���g���Ƃ̐擪�|�C���^
	*/
	std::unordered_map<ComponentBits, std::byte*> m_bit_to_head_pointer;

	/**
	* @brief �R���|�[�l���g���Ƃ̃T�C�Y
	*/
	std::unordered_map<ComponentBits, size_t> m_bit_to_component_size;

	/**
	* @brief �i�[�ł���G���e�B�e�B�̍ő吔
	*/
	uint32_t m_max_entities_capacity;

	/**
	* @brief �i�[����Ă���G���e�B�e�B��
	*/
	uint32_t m_num_entities;

	/**
	* @brief �폜��ړ����N�������Ƀo�[�W�����`�F�b�N�����߂�t���O
	*/
	bool m_needs_version_check;

	/**
	* @brief �󂢂Ă���C���f�b�N�X�̃��X�g
	*/
	std::vector<uint32_t> m_free_slot_indicies;

	/**
	* @brief �G���e�B�e�B�o�[�W�����`�F�b�N�p�̃C���^�t�F�[�X
	*/
	IEntityVersionChecker* m_entity_version_checker;
};

}// !namespace HaraProject::Framework

#endif // !_COMPONENT_DATA_CHUNK_H_
