/**
* @file   EntityManager.h
* @brief  �G���e�B�e�B����N���X��`.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include <cstdint>
#include <unordered_map>

#include "EntityIdAllocater.h"
#include "EntityLocator.h"
#include "EntityValueHandler.h"
#include "ComponentDataChunk.h"
#include "IComponentDataManager.h"

#include "IEntityOperator.h"
#include "IEntityVersionChecker.h"

#ifdef _DEBUG
#include "nlohmann/json.hpp"
#include "GuiItemBase.h"
#include "GuiManager.h"
#endif // _DEBUG

namespace HaraProject::Framework
{

class EntityManager : public IEntityOperator, public IEntityVersionChecker
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param[in] componentDataManager �R���|�[�l���g�f�[�^�}�l�[�W���[
	*/
	EntityManager(IComponentDataManager* componentDataManager);

	/**
	* @brief �ǂݍ��񂾃G���e�B�e�B���쐬����
	* @param[in] entityValueHandler �l���i�[���ꂽ�G���e�B�e�B�̃f�[�^
	*/
	uint32_t CreateLoadedEntity(std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler)override;

	/**
	* @brief �G���e�B�e�B���폜����
	* @param[in] id �G���e�B�e�BID
	*/
	void DeleteEntity(uint32_t id)override;

	/**
	* @brief �G���e�B�e�B�ɃR���|�[�l���g�f�[�^��ǉ�
	* @param[in] id �G���e�B�e�BID
	* @param[in] bit �R���|�[�l���g���ʃr�b�g
	*/
	void AddComponentData(uint32_t id, ComponentBits bit)override;

	/**
	* @brief �G���e�B�e�B����R���|�[�l���g���폜
	* @param[in] id �G���e�B�e�BID
	* @param[in] bit �R���|�[�l���g���ʃr�b�g
	*/
	void RemoveComponentData(uint32_t id, ComponentBits bit)override;

	/**
	* @brief �G���e�B�e�B����R���|�[�l���g���擾
	* @param[in] id �G���e�B�e�BID
	* @param[in] bit �R���|�[�l���g���ʃr�b�g
	*/
	ComponentDataBase* GetComponentData(uint32_t id, ComponentBits bit)override;

	/**
	* @brief �G���e�B�e�B���w��R���|�[�l���g�������Ă��邩�m�F
	* @param[in] id �G���e�B�e�BID
	* @param[in] bit �R���|�[�l���g���ʃr�b�g
	*/
	bool HasComponentData(uint32_t id, ComponentBits bit)override;

	/**
	* @brief �L���ȃG���e�B�e�B��
	* @param[in] id �G���e�B�e�BID
	* @param[in] version �o�[�W����
	*/
	bool IsValidEntity(uint32_t id, uint32_t version)override;

#ifdef _DEBUG
	/**
	* @brief ��̃G���e�B�e�B���쐬
	*/
	uint32_t CreateEntityEmpty()override;

	/**
	* @brief �G���e�B�e�B�̃f�[�^��Json�ɕϊ�
	* @param[in] id �G���e�B�e�BID
	*/
	nlohmann::json ConvertEntityToJson(uint32_t id);

	/**
	* @brief �G���e�B�e�B�̃f�[�^���擾
	* @param[in] id �G���e�B�e�BID
	*/
	std::unordered_map<ComponentBits, ComponentDataBase*> GetEntityData(uint32_t id);
#endif // _DEBUG


private:
	/**
	* @brief �G���e�B�e�BID�Ǘ�
	*/
	EntityIdAllocater m_entity_id_allocater;

	/**
	* @brief �G���e�B�e�B�i�[�ʒu�Ǘ�
	*/
	EntityLocator m_entity_locator;

	/**
	* @brief �R���|�[�l���g�f�[�^�Ǘ�
	*/
	IComponentDataManager* m_component_data_manager;
};

}// !namespace HaraProject::Framework

#endif // !_ENTITY_MANAGER_H_