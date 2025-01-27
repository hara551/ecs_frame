/**
* @file   IEntityManager.h
* @brief  �G���e�B�e�B����C���^�[�t�F�[�X.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _IENTITY_OPERATOR_H_
#define _IENTITY_OPERATOR_H_

#include <cstdint>
#include <unordered_map>

#include "ComponentMask.h"
#include "ComponentDataBase.h"

namespace HaraProject::Framework
{

/**
* @brief �G���e�B�e�B����C���^�[�t�F�[�X
*/
class IEntityOperator
{
public:
	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~IEntityOperator() = default;

	/**
	* @brief �ǂݍ��񂾃G���e�B�e�B���쐬����
	* @param[in] entityValueHandler �l���i�[���ꂽ�G���e�B�e�B�̃f�[�^
	*/
	virtual uint32_t CreateLoadedEntity(std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler) = 0;

	/**
	* @brief �G���e�B�e�B���폜����
	* @param[in] id �G���e�B�e�BID
	*/
	virtual void DeleteEntity(uint32_t id) = 0;

	/**
	* @brief �G���e�B�e�B�ɃR���|�[�l���g�f�[�^��ǉ�
	* @param[in] id �G���e�B�e�BID
	* @param[in] bit �R���|�[�l���g���ʃr�b�g
	*/
	virtual void AddComponentData(uint32_t id, ComponentBits bit) = 0;

	/**
	* @brief �G���e�B�e�B����R���|�[�l���g���폜
	* @param[in] id �G���e�B�e�BID
	* @param[in] bit �R���|�[�l���g���ʃr�b�g
	*/
	virtual void RemoveComponentData(uint32_t id, ComponentBits bit) = 0;

	/**
	* @brief �G���e�B�e�B����R���|�[�l���g���擾
	* @param[in] id �G���e�B�e�BID
	* @param[in] bit �R���|�[�l���g���ʃr�b�g
	*/
	virtual ComponentDataBase* GetComponentData(uint32_t id, ComponentBits bit) = 0;

	/**
	* @brief �G���e�B�e�B���w��R���|�[�l���g�������Ă��邩�m�F
	* @param[in] id �G���e�B�e�BID
	* @param[in] bit �R���|�[�l���g���ʃr�b�g
	*/
	virtual bool HasComponentData(uint32_t id, ComponentBits bit) = 0;

	
#ifdef _DEBUG
	/**
	* @brief ��̃G���e�B�e�B���쐬
	*/
	virtual uint32_t CreateEntityEmpty() = 0;
#endif // _DEBUG

};

}// !namespace HaraProject::Framework

#endif // !_IENTITY_OPERATOR_H_