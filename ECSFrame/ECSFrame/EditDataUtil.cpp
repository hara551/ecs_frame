#include <map>
#include <string>
#include <memory>
#include <fstream>

#include "nlohmann/json.hpp"

#include "FileUtil.h"
#include "ComponentRegistry.h"
#include "SystemRegistry.h"

#include "EditDataUtil.h"

#include "ComponentDataBase.h"
#include "ComponentMask.h"
#include "SystemBase.h"
#include "SystemMask.h"

#include "SystemManager.h"

namespace HaraProject::Framework {

static const char* SUBSCENES_JSON_KEY = "SubScenes";
static const uint8_t JSON_DATA_DUMP = 4;

/**
* @brief �n���h�������
* @param[in] entityValueHandler �n���h��
*/
void ReleaceEntityValueHandler(std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler)
{
	for (auto& component : entityValueHandler)
	{
		if (component.second != nullptr)
		{
			delete component.second;
			component.second = nullptr;
		}
	}
}
//
///**
//* @brief ���[���h��Json�f�[�^���C���X�^���X�����A�T�u�V�[�����ƂɎ擾
//*/
//std::unordered_map<std::string, std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>>> InstantiateWorldJsonForEditor(std::string worldName, bool isAfterPlay)
//{
//	std::unordered_map<std::string, std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>>> world_entity_instances{};
//
//	// �Z�[�u�̗p�r�ɉ����ăp�X�쐬�̎�ނ�ݒ�
//	FileType file_type = isAfterPlay ? FileType::BeforePlayData : FileType::WorldData;
//
//	if (!FileExists(file_type, worldName.c_str()))
//	{
//		return world_entity_instances;
//	}
//
//	//--- json�t�@�C���ǂݍ���
//	std::string path = CreatePath(file_type, worldName.c_str());
//
//	std::ifstream in_file(path);
//	if (in_file.is_open())
//	{
//		// json�I�u�W�F�N�g�Ɋi�[
//		nlohmann::json world_json;
//		in_file >> world_json;
//		in_file.close();
//
//		nlohmann::json subscenes_data = world_json[SUBSCENES_JSON_KEY];
////		nlohmann::json system_data = world_json[SYSTEM_JSON_KEY];
//
//		// �T�u�V�[�����Ƃɒl��ێ������I�u�W�F�N�g���쐬
//		for (auto subscene = subscenes_data.begin(); subscene != subscenes_data.end(); ++subscene)
//		{
//			std::string subscene_name = subscene.key();
//			std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>> subscene_entity_instances =
//				InstantiateSubSceneJson(subscene_name);
//
//			for (auto& handle : subscene_entity_instances)
//			{
//				world_entity_instances[subscene_name].push_back(handle);
//			}
//		}
//	}
//	return world_entity_instances;
//}
///**
//* @brief ���[���h��Json�f�[�^���C���X�^���X�����Ď擾
//* @param[in] worldName ���[���h��
//*/
//std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>>InstantiateWorldJson(std::string worldName)
//{
//	std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>> world_entity_instances{};
//
//	if (!FileExists(FileType::WorldData, worldName.c_str()))
//	{
//		return world_entity_instances;
//	}
//
//	// json�t�@�C���ǂݍ���
//	std::string path = CreatePath(FileType::WorldData, worldName.c_str());
//	std::ifstream in_file(path);
//	if (in_file.is_open())
//	{
//		// json�I�u�W�F�N�g�Ɋi�[
//		nlohmann::json world_json;
//		in_file >> world_json;
//		in_file.close();
//
//		nlohmann::json subscenes_data = world_json[SUBSCENES_JSON_KEY];
//
//		// �T�u�V�[�����Ƃɒl��ێ������I�u�W�F�N�g���쐬
//		for (auto subscene = subscenes_data.begin(); subscene != subscenes_data.end(); ++subscene)
//		{
//			std::string subscene_name = subscene.key();
//			std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>> subscene_entity_instances =
//				InstantiateSubSceneJson(subscene_name);
//
//			for (auto& handle : subscene_entity_instances)
//			{
//				world_entity_instances.push_back(handle);
//			}
//		}
//	}
//	return world_entity_instances;
//}
//
///**
//* @brief �T�u�V�[���̃G���e�B�e�B��Json����C���X�^���X�����Ď擾
//* @param[in] subSceneName �T�u�V�[����
//*/
//std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>> InstantiateSubSceneJson(std::string subSceneName, bool isAfterPlay)
//{
//	std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>> subscene_entity_handlers{};
//
//	FileType file_type = isAfterPlay ? FileType::BeforePlayData : FileType::SubSceneData;
//
//	if (!FileExists(file_type, subSceneName.c_str()))return subscene_entity_handlers;
//
//	// �t�@�C���ǂݍ���
//	std::string path = CreatePath(file_type, subSceneName.c_str());
//	std::ifstream in_file(path);
//	if (in_file.is_open())
//	{
//		// json�I�u�W�F�N�g�Ɋi�[
//		nlohmann::json subscene_data;
//		in_file >> subscene_data;
//		in_file.close();
//
//		// �G���e�B�e�B���ƂɃC���X�^���X�����Ċi�[
//		for (const auto& entityData : subscene_data)
//		{
//			std::unordered_map<ComponentBits, ComponentDataBase*> entity_value_hanldler;
//			for (auto component_data = entityData.begin(); component_data != entityData.end(); ++component_data)
//			{
//				// �R���|�[�l���g�����环�ʃr�b�g���擾
//				std::string component_name = component_data.key();
//				ComponentBits mask = ComponentRegistry::GetBitByName(component_name);
//
//				// ���ʃr�b�g����C���X�^���X���쐬
//				ComponentDataBase* instance = ComponentRegistry::Constructor(mask);
//				// Json�f�[�^����C���X�^���X�֒l��ݒ�
//				instance->SetDataFromJson(entityData[component_name]);
//
//				// �R���|�[�l���g���ƃC���X�^���X���}�b�v�֒ǉ�
//				if (!entity_value_hanldler.contains(mask))
//				{
//					entity_value_hanldler.emplace(mask, instance);
//				}
//			}
//			subscene_entity_handlers.push_back(entity_value_hanldler);
//		}
//	}
//	return subscene_entity_handlers;
//}
//
///**
//* @brief ���[���h�̏�Ԃ�Json�t�@�C���ɕۑ�
//* @param[in] editorManager �G�f�B�^�[�}�l�[�W���[
//*/
//void WriteWorldJsonData(EditorManager* editorManager, bool isBeforePlay)
//{
//	nlohmann::json world_json_data{};
//	nlohmann::json subscene_json_data{};
//
//	//--- ���[���h�̊T�v��ۑ�
//	// �T�u�V�[�����Ƃ̃G���e�B�e�BID���擾
//	std::unordered_map<std::string, std::vector<uint32_t>> subscene_to_entities = editorManager->GetSubSceneToEntities();
//	std::unordered_map<std::string, Transform> subscene_to_transforms = editorManager->GetSubSceneToTransforms();
//
//	for (const auto& subscene : subscene_to_entities)
//	{
//		// �T�u�V�[�����ƃg�����X�t�H�[�����L�^
////		world_json_data[SUBSCENES_JSON_KEY].push_back(subscene.first);
//		world_json_data[SUBSCENES_JSON_KEY][subscene.first] = subscene_to_transforms[subscene.first].WriteDataToJson();
//	}
//
//	//--- �t�@�C����������
//	FileType file_type = isBeforePlay ? FileType::BeforePlayData : FileType::WorldData;
//	std::string path = CreatePath(file_type, editorManager->GetEditWorldName().c_str());
//
//	std::ofstream out_file(path);
//	if (out_file.is_open())
//	{
//		out_file << world_json_data.dump(JSON_DATA_DUMP);
//		out_file.close();
//	}
//
//	//--- �T�u�V�[�����̃G���e�B�e�B�̏�Ԃ�ۑ�
//	for (const auto& subscene : subscene_to_entities)
//	{
//		// �T�u�V�[�����ƂɃZ�[�u
//		WriteSubSceneJsonData(editorManager, subscene.first, isBeforePlay);
//	}
//}
//
///**
//* @brief �T�u�V�[���̏�Ԃ�Json�t�@�C���ɕۑ�
//* @param[in] editorManager �G�f�B�^�[�}�l�[�W���[
//* @param[in] subSceneName �T�u�V�[����
//*/
//void WriteSubSceneJsonData(EditorManager* editorManager, std::string subSceneName, bool isBeforePlay)
//{
//	EntityManager* entity_manager = editorManager->GetEntityManager();
//	std::vector<uint32_t> entities = editorManager->GetSubSceneToEntities()[subSceneName];
//
//	nlohmann::json subscene_json_data{};
//	for (const auto& entity : entities)
//	{
//		subscene_json_data.push_back(entity_manager->ConvertEntityToJson(entity));
//	}
//
//	FileType file_type = isBeforePlay ? FileType::BeforePlayData : FileType::SubSceneData;
//	std::string path = CreatePath(file_type, subSceneName.c_str());
//
//	std::ofstream out_file(path);
//	if (out_file.is_open())
//	{
//		out_file << subscene_json_data.dump(JSON_DATA_DUMP);
//		out_file.close();
//	}
//}
//
///**
//* @brief �T�u�V�[�����Ƃ̃g�����X�t�H�[�����擾
//* @param[in] worldName ���[���h��
//*/
//std::unordered_map<std::string, Transform> ReadSubSubSceneTransforms(std::string worldName)
//{
//	std::unordered_map<std::string, Transform> subscene_to_transform{};
//
//	if (!FileExists(FileType::WorldData, worldName.c_str()))
//	{
//		return subscene_to_transform;
//	}
//
//	// json�t�@�C���ǂݍ���
//	std::string path = CreatePath(FileType::WorldData, worldName.c_str());
//	std::ifstream in_file(path);
//	if (in_file.is_open())
//	{
//		// json�I�u�W�F�N�g�Ɋi�[
//		nlohmann::json world_json;
//		in_file >> world_json;
//		in_file.close();
//
//		nlohmann::json subscenes_data = world_json[SUBSCENES_JSON_KEY];
//
//		// �T�u�V�[�����Ƃɒl��ێ������I�u�W�F�N�g���쐬
//		for (auto subscene = subscenes_data.begin(); subscene != subscenes_data.end(); ++subscene)
//		{
//			std::string subscene_name = subscene.key();
//
//			if (subscene.value().contains(Transform::TRANSFORM_NAME))
//			{
//				Transform transform{};
//				transform.SetDataFromJson(subscene.value()[Transform::TRANSFORM_NAME]);
//
//				subscene_to_transform[subscene_name] = transform;
//			}
//		}
//	}S
//	return subscene_to_transform;
//}

} // !namespace HaraProject::Framework::EditDataUtil