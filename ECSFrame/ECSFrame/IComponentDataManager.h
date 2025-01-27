/**
* @file   IComponentDataManager.h
* @brief  �R���|�[�l���g�f�[�^����C���^�[�t�F�[�X.
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
* @brief�@�R���|�[�l���g�f�[�^����C���^�[�t�F�[�X
*/
class IComponentDataManager
{
public:
	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~IComponentDataManager() = default;

	/**
	* @brief �G���e�B�e�B�ɃR���|�[�l���g�f�[�^��ǉ�
	* @param[in] id �G���e�B�e�BID
	* @param[in] newVersion �ړ���̃`�����N�Ŏg���o�[�W����
	* @param[in] chunk �`�����N�ւ̃|�C���^
	* @param[in] indexInChunk �`�����N���̃C���f�b�N�X
	* @param[in] bit �R���|�[�l���g���ʃr�b�g
	*/
	virtual ComponentDataChunk* AddComponentData(uint32_t id, uint32_t newVersion, ComponentDataChunk* chunk, uint32_t indexInChunk, ComponentBits bit) = 0;
	
	/**
	* @brief �G���e�B�e�B����R���|�[�l���g���폜
	* @param[in] id �G���e�B�e�BID
	* @param[in] newVersion �ړ���̃`�����N�Ŏg���o�[�W����
	* @param[in] chunk �`�����N�ւ̃|�C���^
	* @param[in] indexInChunk �`�����N���̃C���f�b�N�X
	* @param[in] bit �R���|�[�l���g���ʃr�b�g
	*/
	virtual ComponentDataChunk* RemoveComponentData(uint32_t id, uint32_t newVersion, ComponentDataChunk* chunk, uint32_t indexInChunk, ComponentBits bit) = 0;

	/**
	* @brief �G���e�B�e�B���i�[
	* @param[in] id �G���e�B�e�BID
	* @param[in] version �o�[�W����
	* @param[in] entityValueHandler �l���i�[���ꂽ�G���e�B�e�B�̃f�[�^
	* @return �G���e�B�e�B���i�[�����`�����N�̃|�C���^
	*/
	virtual ComponentDataChunk* InsertComponentDataToChunk(uint32_t id, uint32_t version, std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler) = 0;

	/**
	* @brief �G���e�B�e�B�o�[�W�����`�F�b�N�p�̃C���^�t�F�[�X��ݒ�
	* @param[in] entityVersionChecker �G���e�B�e�B�o�[�W�����`�F�b�N�p�̃C���^�t�F�[�X�̃|�C���^
	*/
	virtual void SetEntityVersionChecker(IEntityVersionChecker* entityVersionChecker) = 0;
};

}// !namespace HaraProject::Framework

#endif // !_ICOMPONENT_DATA_MANAGER_H_