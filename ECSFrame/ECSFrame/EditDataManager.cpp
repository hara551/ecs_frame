
#include <string>
#include <cstdint>
#include <unordered_map>
#include <vector>
#include <fstream>

#include "nlohmann/json.hpp"

#include "ComponentMask.h"
#include "ComponentDataBase.h"
#include "EntityTypes.h"
#include "ComponentRegistry.h"
#include "FileUtil.h"
#include "SubSceneManager.h"
#include "Transform.h"
#include "ComponentDataBase.h"
#include "EditDataManager.h"

namespace HaraProject::Framework {

/**
* @brief Json�t�@�C�����ł̃T�u�V�[���ꗗ�u���b�N�̃L�[
*/
static const char* SUBSCENES_JSON_KEY = "SubScenes";

/**
* @brief Json�t�@�C�����ł̃T�E���h�ꗗ�u���b�N�̃L�[
*/
static const char* SOUNDS_JSON_KEY = "Sounds";

/**
* @brief Json�t�@�C�������o�����̗v�f���Ƃ̃C���f���g��
*/
static const uint8_t JSON_DUMP_NUM = 4;

/**
* @brief ���[���h�̑S�G���e�B�e�B�f�[�^�����[�h
* @param[in] worldName ���[���h��
*/
EntityDataList EditDataManager::LoadWorldData(std::string worldName)
{
	EntityDataList world_entity_datas{};

	// �t�@�C�������݂��Ȃ���΋�ŕԂ�
	FileType world_data_type = FileType::WorldData;
	if (!FileExists(world_data_type, worldName.c_str()))
	{
		return world_entity_datas;
	}

	std::string path = CreatePath(world_data_type, worldName.c_str());

	nlohmann::json world_json = ReadJsonFile(path);

	// ���ڂ��ƂɎ擾
	nlohmann::json subscenes_json = world_json[SUBSCENES_JSON_KEY];

	for (auto subscene_json = subscenes_json.begin(); subscene_json != subscenes_json.end(); ++subscene_json)
	{
		// �T�u�V�[�����ƂɃG���e�B�e�B�̒l�����[�h
		std::string subscene_name = subscene_json.key();
		EntityDataList subscene_entitiy_datas = LoadSubSceneData(subscene_name);
		// ���ʂɒǉ�
		world_entity_datas.insert(world_entity_datas.end(), 
			subscene_entitiy_datas.begin(), subscene_entitiy_datas.end());
	}
	return world_entity_datas;
}

/**
* @brief �T�u�V�[�����̑S�G���e�B�e�B�f�[�^�����[�h
* @param[in] subsceneName �T�u�V�[����
*/
EntityDataList EditDataManager::LoadSubSceneData(std::string subsceneName)
{
	EntityDataList subscene_entity_datas{};

	// �t�@�C�������݂��Ȃ���΋�ŕԂ�
	FileType subscene_data_type = FileType::SubSceneData;
	if (!FileExists(subscene_data_type, subsceneName.c_str()))
	{
		return subscene_entity_datas;
	}

	std::string path = CreatePath(subscene_data_type, subsceneName.c_str());
	nlohmann::json subscene_json = ReadJsonFile(path);

	for (const auto& entity_json : subscene_json)
	{
		EntityData entity_data{};
		for (auto component_json = entity_json.begin(); component_json != entity_json.end(); ++component_json)
		{
			// �R���|�[�l���g�����环�ʃr�b�g���擾
			std::string component_name = component_json.key();
			ComponentBits component_bit = ComponentRegistry::GetBitByName(component_name);

			// ���ʃr�b�g����R���X�g���N�^�����s
			ComponentDataBase* component_data = ComponentRegistry::Constructor(component_bit);
			// json����R���|�[�l���g�ɒl��ݒ�
			component_data->SetDataFromJson(entity_json[component_name]);

			// �R���|�[�l���g���G���e�B�e�B�f�[�^�ɒǉ�
			entity_data.emplace(component_bit, component_data);
		}
		// ���ʂɒǉ�
		subscene_entity_datas.push_back(entity_data);
	}
	return subscene_entity_datas;
}

/**
* @brief �ǂݍ��݂Ŏg�����G���e�B�e�B�̃f�[�^���������
* @param[in] loadedEntityData �g���I������G���e�B�e�B�f�[�^
*/
void EditDataManager::ReleaceLoadedEntityData(EntityData loadedEntityData)
{
	for (auto& itr : loadedEntityData)
	{
		if (itr.second != nullptr)
		{
			delete itr.second;
			itr.second = nullptr;
		}
	}
}

/**
* @brief ���[���h�Ŏg�p����T�E���h�ꗗ���擾
* @param[in] worldName ���[���h��
*/
std::unordered_map<SoundManager::SoundType, std::vector<std::string>> EditDataManager::LoadSoundNames(std::string worldName)
{
	std::unordered_map<SoundManager::SoundType, std::vector<std::string>> world_sound_names{};

	// �t�@�C�������݂��Ȃ���΋�ŕԂ�
	FileType world_data_type = FileType::WorldData;
	if (!FileExists(world_data_type, worldName.c_str()))
	{
		return world_sound_names;
	}

	std::string path = CreatePath(world_data_type, worldName.c_str());

	nlohmann::json world_json = ReadJsonFile(path);
	// �T�E���h�ꗗ�̃u���b�N�𒊏o
	if (!world_json.contains(SOUNDS_JSON_KEY))
	{
		return world_sound_names; // �T�E���h��񂪂Ȃ��ꍇ�͋�ŕԂ�
	}

	nlohmann::json sounds_json = world_json[SOUNDS_JSON_KEY];

	// �T�E���h�̎�ށiSE, BGM�j�����[�v����
	for (const auto& [sound_type, sound_list] : sounds_json.items())
	{
		SoundManager::SoundType type;

		// �T�E���h�^�C�v�𔻒�
		if (sound_type == "SE")
		{
			type = SoundManager::SE;
		}
		else if (sound_type == "BGM")
		{
			type = SoundManager::BGM;
		}
		else
		{
			continue; // SE, BGM�ȊO�̃L�[�̓X�L�b�v
		}

		// �T�E���h�t�@�C�������擾
		if (sound_list.is_array())
		{
			for (const auto& sound_file : sound_list)
			{
				if (sound_file.is_string())
				{
					world_sound_names[type].push_back(sound_file.get<std::string>());
				}
			}
		}
	}
	return world_sound_names;
}

/**
* @brief �Q�[���̍ŏ��Ƀ��[�h���郏�[���h�����擾
*/
std::string EditDataManager::LoadBeginningWorldName()
{
	// �t�@�C�������݂��Ȃ���΋�ŕԂ�
	if (!FileExists(FileType::BeginWorldData, "Initialize"))return std::string();
	
	// �p�X�쐬
	std::string path = CreatePath(FileType::BeginWorldData, "Initialize");
	
	// �ǂݍ���
	nlohmann::json initialize_json = ReadJsonFile(path);

	// �ŏ��Ƀ��[�h���郏�[���h�����擾
	std::string beginning_world_name = initialize_json[0].get<std::string>();
	return beginning_world_name;
}

/**
* @brief Json�t�@�C���̓ǂݎ��
* @param[in] path �t�@�C���p�X
*/
nlohmann::json EditDataManager::ReadJsonFile(std::string path)
{
	nlohmann::json jsonData{};

	std::ifstream in_file(path);
	if (in_file.is_open())
	{
		in_file >> jsonData;
		in_file.close();
	}

	return jsonData;
}

/**
* @brief Json�t�@�C���̏����o��
* @param[in] path �t�@�C���p�X
* @param[in] jsonData �����o��Json�I�u�W�F�N�g
*/
void EditDataManager::WriteJsonFile(std::string path, nlohmann::json jsonData)
{
	std::ofstream out_file(path);
	if (out_file.is_open())
	{
		out_file << jsonData.dump(JSON_DUMP_NUM);
		out_file.close();
	}
}

#ifdef _DEBUG
/**
* @brief ���[���h���̃G���e�B�e�B�f�[�^���T�u�V�[�����Ƃɂ����[�h
* @param[in] worldName ���[���h��
*/
std::unordered_map<std::string, EntityDataList> EditDataManager::LoadWorldDataForEditor(std::string worldName)
{
	std::unordered_map<std::string, EntityDataList> world_entity_datas{};

	// �t�@�C�������݂��Ȃ���΋�ŕԂ�
	FileType world_data_type = FileType::WorldData;
	if (!FileExists(world_data_type, worldName.c_str()))
	{
		return world_entity_datas;
	}

	std::string path = CreatePath(world_data_type, worldName.c_str());

	nlohmann::json world_json = ReadJsonFile(path);

	// �T�u�V�[���ꗗ�̃u���b�N�𒊏o
	nlohmann::json subscenes_json = world_json[SUBSCENES_JSON_KEY];

	for (auto subscene_json = subscenes_json.begin(); subscene_json != subscenes_json.end(); ++subscene_json)
	{
		// �T�u�V�[�����ƂɃG���e�B�e�B�̒l�����[�h
		std::string subscene_name = subscene_json.key();
		EntityDataList subscene_entity_datas = LoadSubSceneData(subscene_name);

		// ���ʂɒǉ�
		world_entity_datas.emplace(subscene_name, subscene_entity_datas);
	}
	return world_entity_datas;
}

/**
* @brief ���[���h���̃T�u�V�[���̃g�����X�t�H�[�������[�h
* @param[in] worldName ���[���h��
*/
std::unordered_map<std::string, Transform> EditDataManager::LoadSubscenesTransform(std::string worldName)
{
	std::unordered_map<std::string, Transform> subscene_to_transform{};

	// �t�@�C�������݂��Ȃ���΋�ŕԂ�
	FileType world_data_type = FileType::WorldData;
	if (!FileExists(world_data_type, worldName.c_str()))
	{
		return subscene_to_transform;
	}

	std::string path = CreatePath(world_data_type, worldName.c_str());

	nlohmann::json world_json = ReadJsonFile(path);

	// �T�u�V�[���ꗗ�̃u���b�N�𒊏o
	nlohmann::json subscenes_json = world_json[SUBSCENES_JSON_KEY];

	for (auto subscene_json = subscenes_json.begin(); subscene_json != subscenes_json.end(); ++subscene_json)
	{
		// �T�u�V�[���̃g�����X�t�H�[�����擾
		std::string subscene_name = subscene_json.key();
		Transform transform{};
		transform.SetDataFromJson(subscene_json.value()[Transform::TRANSFORM_NAME]);

		// ���ʂɒǉ�
		subscene_to_transform.emplace(subscene_name, transform);
	}
	return subscene_to_transform;
}

/**
* @brief ���[���h�f�[�^��Json�ɕۑ�
* @param[in] worldName ���[���h��
* @param[in] entityManager �G���e�B�e�B�}�l�[�W���[
* @param[in] subsceneDatas �T�u�V�[����񃊃X�g
*/
void EditDataManager::SaveWorldData(std::string worldName, EntityManager* entityManager,
	std::unordered_map<std::string, SubsceneManager::SubsceneData> subsceneDatas)
{
	nlohmann::json world_json{};
	for (auto& [subscene_name, subscene_data] : subsceneDatas)
	{
		// �T�u�V�[�����ƃg�����X�t�H�[����Json�I�u�W�F�N�g�Ɋi�[
		world_json[SUBSCENES_JSON_KEY][subscene_name] = subscene_data.transform.WriteDataToJson();

		// �T�u�V�[�����̃G���e�B�e�B�̏�Ԃ�ۑ�
		SaveSubsceneData(subscene_name, entityManager, subscene_data);
	}
	// �T�u�V�[�����ƃg�����X�t�H�[����Json�t�@�C���ɏ����o��
	std::string path = CreatePath(FileType::WorldData, worldName.c_str());
	WriteJsonFile(path, world_json);
}

/**
* @brief �T�u�V�[���f�[�^��Json�ɕۑ�
* @param[in] subsceneName �T�u�V�[����
* @param[in] entityManager �G���e�B�e�B�}�l�[�W���[
* @param[in] subsceneData �T�u�V�[�����
*/
void EditDataManager::SaveSubsceneData(std::string subsceneName, EntityManager* entityManager, SubsceneManager::SubsceneData subsceneData)
{
	nlohmann::json subscene_json{};
	for (const auto& entity : subsceneData.entities)
	{
		// �G���e�B�e�B�̃f�[�^��Json�I�u�W�F�N�g�Ɋi�[
		subscene_json.push_back(entityManager->ConvertEntityToJson(entity));
	}
	// �T�u�V�[�����̃G���e�B�e�B�̃f�[�^��Json�t�@�C���ɏ����o��
	std::string path = CreatePath(FileType::SubSceneData, subsceneName.c_str());
	WriteJsonFile(path, subscene_json);
}
#endif // _DEBUG


}// !namespace HaraProject::Framework