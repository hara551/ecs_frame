/**
* @file   ComponentDataManager.h
* @brief  �R���|�[�l���g�f�[�^�Ǘ��N���X��`.
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
* @brief �R���|�[�l���g�f�[�^�Ǘ��N���X
*/
class ComponentDataManager : public IComponentDataManager, public IChunkProvider
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	ComponentDataManager();

	/**
	* @brief �f�X�g���N�^
	*/
	~ComponentDataManager();

	/**
	* @brief �G���e�B�e�B�ɃR���|�[�l���g�f�[�^��ǉ�
	* @param[in] id �G���e�B�e�BID
	* @param[in] newVersion �ړ���̃`�����N�Ŏg���o�[�W����
	* @param[in] chunk �`�����N�ւ̃|�C���^
	* @param[in] indexInChunk �`�����N���̃C���f�b�N�X
	* @param[in] bit �R���|�[�l���g���ʃr�b�g
	*/
	ComponentDataChunk* AddComponentData(uint32_t id, uint32_t newVersion, ComponentDataChunk* chunk, uint32_t indexInChunk, ComponentBits bit)override;

	/**
	* @brief �G���e�B�e�B����R���|�[�l���g���폜
	* @param[in] id �G���e�B�e�BID
	* @param[in] newVersion �ړ���̃`�����N�Ŏg���o�[�W����
	* @param[in] chunk �`�����N�ւ̃|�C���^
	* @param[in] indexInChunk �`�����N���̃C���f�b�N�X
	* @param[in] bit �R���|�[�l���g���ʃr�b�g
	*/
	ComponentDataChunk* RemoveComponentData(uint32_t id, uint32_t newVersion, ComponentDataChunk* chunk, uint32_t indexInChunk, ComponentBits bit)override;

	/**
	* @brief �G���e�B�e�B���i�[
	* @param[in] id �G���e�B�e�BID
	* @param[in] version �o�[�W����
	* @param[in] entityValueHandler �l���i�[���ꂽ�G���e�B�e�B�̃f�[�^
	* @return �G���e�B�e�B���i�[�����`�����N�̃|�C���^
	*/
	ComponentDataChunk* InsertComponentDataToChunk(uint32_t id, uint32_t version, std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler)override;

	/**
	* @brief �G���e�B�e�B�o�[�W�����`�F�b�N�p�̃C���^�t�F�[�X��ݒ�
	* @param[in] entityVersionChecker �G���e�B�e�B�o�[�W�����`�F�b�N�p�̃C���^�t�F�[�X�̃|�C���^
	*/
	void SetEntityVersionChecker(IEntityVersionChecker* entityVersionChecker)override;

	/**
	* @brief �w��̑g�̃R���|�[�l���g�f�[�^����舵���`�����N���擾
	* @param[in] mask �R���|�[�l���g���ʃr�b�g
	*/
	std::vector<ComponentDataChunk*> FindChunks(ComponentBits mask)override;

	/**
	* @brief �`�����N���̃G���e�B�e�B�̃o�[�W�����`�F�b�N���s��
	*/
	void CheckChunkEntitiesVersion();

private:
	/**
	* @brief �w��̑g�ŋ󂫂̂���`�����N���擾
	* @param[in] mask �R���|�[�l���g�̑g������\���}�X�N
	*/
	ComponentDataChunk* FindChunkForComponents(ComponentBits mask);

	/**
	* @brief �n���h���Ɋ܂܂ꂽ�R���|�[�l���g�̑g�݂ɉ��������ʃr�b�g���擾
	* @param[in] entityValueHandler �l���i�[���ꂽ�G���e�B�e�B�̃f�[�^
	*/
	ComponentBits GetMaskByEntityValueHandler(const std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler);

	/**
	* @brief �R���|�[�l���g�g�ݍ��킹�̎��ʃr�b�g�ƃ`�����N�̃}�b�v
	*/
	std::unordered_map <ComponentBits, std::vector <ComponentDataChunk*>> m_bit_to_chunks;

	/**
	* @brief �G���e�B�e�B�o�[�W�����`�F�b�N�p�̃C���^�t�F�[�X
	*/
	IEntityVersionChecker* m_entity_version_checker;
};

}// namespace HaraProject::Framework

#endif // !_COMPONENT_DATA_MANAGER_H_