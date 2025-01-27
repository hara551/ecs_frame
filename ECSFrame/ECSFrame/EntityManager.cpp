
#include "EditDataUtil.h"
#include "EntityIdAllocater.h"
#include "ComponentDataChunk.h"
#include "IComponentDataManager.h"

#include "EntityManager.h"

#include "EntityName.h"
#include "Transform.h"
#include "ComponentMask.h"

namespace HaraProject::Framework
{

/**
* @brief �R���X�g���N�^
* @param[in] componentDataManager �R���|�[�l���g�f�[�^�}�l�[�W���[
*/
EntityManager::EntityManager(IComponentDataManager* componentDataManager)
	: m_component_data_manager(componentDataManager)
{
	m_component_data_manager->SetEntityVersionChecker(this);
}

/**
* @brief �ǂݍ��񂾃G���e�B�e�B���쐬����
* @param[in] entityValueHandler �l���i�[���ꂽ�G���e�B�e�B�̃f�[�^
*/
uint32_t EntityManager::CreateLoadedEntity(std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler)
{
	// ���p�\��ID���擾
	EntityIdAllocater::EntityHandle entity_handle =  m_entity_id_allocater.AssignUsableId();

	// �G���e�B�e�B���i�[���A�i�[�����`�����N���擾
	ComponentDataChunk* chunk = m_component_data_manager->InsertComponentDataToChunk(
		entity_handle.id, entity_handle.version, entityValueHandler
	);
	// ID����`�����N���̃C���f�b�N�X���擾
	uint32_t indexInChunk = chunk->GetIndex(entity_handle.id);

	// �G���e�B�e�B�̊i�[�ʒu��o�^
	m_entity_locator.RegisterLocation(entity_handle.id, chunk, indexInChunk);

	return entity_handle.id;
}

#ifdef _DEBUG
/**
* @brief ��̃G���e�B�e�B���쐬
*/
uint32_t EntityManager::CreateEntityEmpty()
{
	// ���p�\��ID���擾
	EntityIdAllocater::EntityHandle entity_handle = m_entity_id_allocater.AssignUsableId();

	std::unordered_map<ComponentBits, ComponentDataBase*> entity_value_handler{};

	// �G���e�B�e�B���쐬
	EntityName* entity_name = new EntityName();
	// �f�t�H���g�Ŗ��O��ݒ�
	std::string empty_name = "Empty" + std::to_string(entity_handle.id);
	strcpy_s(entity_name->name,empty_name.c_str());

	entity_value_handler[ComponentMask<EntityName>::bit] = entity_name;

	// �g�����X�t�H�[���쐬
	entity_value_handler[ComponentMask<Transform>::bit] = new Transform();

	// �G���e�B�e�B���i�[���A�i�[�ʒu��o�^
	ComponentDataChunk* chunk = m_component_data_manager->InsertComponentDataToChunk(
		entity_handle.id, entity_handle.version, entity_value_handler
	);
	uint32_t indexInChunk = chunk->GetIndex(entity_handle.id);

	m_entity_locator.RegisterLocation(entity_handle.id, chunk, indexInChunk);

	// �i�[�Ɏg�����n���h�������
	ReleaceEntityValueHandler(entity_value_handler);

	return entity_handle.id;
}
#endif // _DEBUG

/**
* @brief �G���e�B�e�B���폜����
* @param[in] id �G���e�B�e�BID
*/
void EntityManager::DeleteEntity(uint32_t id)
{
	// �i�[�ʒu�擾
	EntityLocator::EntityLocation location =  m_entity_locator.GetLocation(id);

	// �������Ă���`�����N�̃o�[�W�����`�F�b�N�t���O��������
	location.chunk->SetNeedsVersionCheck(true);

	// �G���e�B�e�BID���󂯂�
	m_entity_id_allocater.FreeUpId(id);
}

/**
* @brief �G���e�B�e�B�ɃR���|�[�l���g�f�[�^��ǉ�
* @param[in] id �G���e�B�e�BID
* @param[in] bit �R���|�[�l���g���ʃr�b�g
*/
void EntityManager::AddComponentData(uint32_t id, ComponentBits bit)
{
	// �i�[�ʒu�擾
	EntityLocator::EntityLocation location = m_entity_locator.GetLocation(id);

	// �`�����N���ړ����邱�ƂɂȂ邽�߃o�[�W�������X�V���擾
	uint32_t new_version = m_entity_id_allocater.IncreaceValidVersion(id);

	// �R���|�[�l���g�f�[�^�̒ǉ����˗����A�ړ���̃`�����N���擾
	ComponentDataChunk* located_chunk = m_component_data_manager->AddComponentData(
		id, new_version, location.chunk, location.indexInChunk, bit
	);
	// �i�[���ꂽ�C���f�b�N�X���擾
	uint32_t indexInChunk = located_chunk->GetIndex(id);
	// �i�[�ʒu��o�^
	m_entity_locator.RegisterLocation(id, located_chunk, indexInChunk);
}

/**
* @brief �G���e�B�e�B����R���|�[�l���g���폜
* @param[in] id �G���e�B�e�BID
* @param[in] bit �R���|�[�l���g���ʃr�b�g
*/
void EntityManager::RemoveComponentData(uint32_t id, ComponentBits bit)
{
	// �i�[�ʒu�擾
	EntityLocator::EntityLocation location = m_entity_locator.GetLocation(id);

	// �`�����N���ړ����邱�ƂɂȂ邽�߃o�[�W�������X�V���擾
	uint32_t new_version = m_entity_id_allocater.IncreaceValidVersion(id);

	// �R���|�[�l���g�f�[�^�̍폜���˗����A�ړ���̃`�����N���擾
	ComponentDataChunk* located_chunk = m_component_data_manager->RemoveComponentData(
		id, new_version, location.chunk, location.indexInChunk, bit
	);
	// �i�[���ꂽ�C���f�b�N�X���擾
	uint32_t indexInChunk = located_chunk->GetIndex(id);
	// �i�[�ʒu��o�^
	m_entity_locator.RegisterLocation(id, located_chunk, indexInChunk);
}

/**
* @brief �G���e�B�e�B����R���|�[�l���g���擾
* @param[in] id �G���e�B�e�BID
* @param[in] bit �R���|�[�l���g���ʃr�b�g
*/
ComponentDataBase* EntityManager::GetComponentData(uint32_t id, ComponentBits bit)
{
	EntityLocator::EntityLocation location = m_entity_locator.GetLocation(id);

	ComponentDataBase* component_data{};
	if (location.chunk != nullptr)
	{
		component_data = location.chunk->CalculateComponentDataPointer(bit, location.indexInChunk);
	}

	return component_data;
}

/**
* @brief �G���e�B�e�B���w��R���|�[�l���g�������Ă��邩�m�F
* @param[in] id �G���e�B�e�BID
* @param[in] bit �R���|�[�l���g���ʃr�b�g
*/
bool EntityManager::HasComponentData(uint32_t id, ComponentBits bit)
{
	ComponentDataBase* component = GetComponentData(id, bit);
	return component != nullptr;
}

/**
* @brief �L���ȃG���e�B�e�B��
* @param[in] id �G���e�B�e�BID
* @param[in] version �o�[�W����
*/
bool EntityManager::IsValidEntity(uint32_t id, uint32_t version)
{
	return m_entity_id_allocater.IsValidId(id, version);
}

#ifdef _DEBUG
/**
* @brief �G���e�B�e�B�̃f�[�^��Json�ɕϊ�
* @param[in] id �G���e�B�e�BID
*/
nlohmann::json EntityManager::ConvertEntityToJson(uint32_t id)
{
	EntityLocator::EntityLocation location = m_entity_locator.GetLocation(id);

	std::unordered_map<ComponentBits, ComponentDataBase*> entity_data_handle = location.chunk->GetEntityData(location.indexInChunk);

	nlohmann::json entity_json_data{};
	for (const auto& component : entity_data_handle)
	{
		entity_json_data.merge_patch(component.second->WriteDataToJson());
	}

	// �g�p�����n���h�������
	ReleaceEntityValueHandler(entity_data_handle);

	return entity_json_data;
}

/**
* @brief �G���e�B�e�B�̃f�[�^���擾
* @param[in] id �G���e�B�e�BID
*/
std::unordered_map<ComponentBits, ComponentDataBase*> EntityManager::GetEntityData(uint32_t id)
{
	EntityLocator::EntityLocation location = m_entity_locator.GetLocation(id);
	return location.chunk->GetEntityData(location.indexInChunk);
}
#endif // _DEBUG

}// !namespace HaraProject::Framework