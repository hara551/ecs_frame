/**
* @file   EditDataManager.h
* @brief  �ҏW�f�[�^�Ǘ�.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _EDIT_DATA_MANAGER_H_
#define _EDIT_DATA_MANAGER_H_

#include <string>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "nlohmann/json.hpp"

#include "IEditDataLoader.h"
#include "EntityTypes.h"
#include "EntityManager.h"
#include "Transform.h"
#include "SubSceneManager.h"
#include "SoundManager.h"

namespace HaraProject::Framework {

class EditDataManager : public IEditDataLoader
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	EditDataManager() = default;

	/**
	* @brief �f�X�g���N�^
	*/
	~EditDataManager() = default;

	/**
	* @brief ���[���h���̑S�G���e�B�e�B�f�[�^�����[�h
	* @param[in] worldName ���[���h��
	*/
	EntityDataList LoadWorldData(std::string worldName)override;

	/**
	* @brief �T�u�V�[�����̑S�G���e�B�e�B�f�[�^�����[�h
	* @param[in] subsceneName �T�u�V�[����
	*/
	EntityDataList LoadSubSceneData(std::string subsceneName)override;

	/**
	* @brief �ǂݍ��݂Ŏg�����G���e�B�e�B�̃f�[�^���������
	* @param[in] loadedEntityData �g���I������G���e�B�e�B�f�[�^
	*/
	void ReleaceLoadedEntityData(EntityData loadedEntityData)override;

	/**
	* @brief ���[���h�Ŏg�p����T�E���h�ꗗ���擾
	* @param[in] worldName ���[���h��
	*/
	std::unordered_map<SoundManager::SoundType, std::vector<std::string>> LoadSoundNames(std::string worldName)override;

	/**
	* @brief �Q�[���̍ŏ��Ƀ��[�h���郏�[���h�����擾
	*/
	std::string LoadBeginningWorldName();

	/**
	* @brief Json�t�@�C���̓ǂݎ��
	* @param[in] path �t�@�C���p�X
	*/
	nlohmann::json ReadJsonFile(std::string path);

	/**
	* @brief Json�t�@�C���̏����o��
	* @param[in] path �t�@�C���p�X
	* @param[in] jsonData �����o��Json�I�u�W�F�N�g
	*/
	void WriteJsonFile(std::string path, nlohmann::json jsonData);

#ifdef _DEBUG

	/**
	* @brief ���[���h���̃G���e�B�e�B�f�[�^���T�u�V�[�����Ƃɂ����[�h
	* @param[in] worldName ���[���h��
	*/
	std::unordered_map<std::string, EntityDataList> LoadWorldDataForEditor(std::string worldName);

	/**
	* @brief ���[���h�f�[�^��Json�ɕۑ�
	* @param[in] worldName ���[���h��
	* @param[in] entityManager �G���e�B�e�B�}�l�[�W���[
	* @param[in] subsceneDatas �T�u�V�[����񃊃X�g
	*/
	void SaveWorldData(std::string worldName, EntityManager* entityManager,
		std::unordered_map<std::string, SubsceneManager::SubsceneData> subsceneDatas);

	/**
	* @brief �T�u�V�[���f�[�^��Json�ɕۑ�
	* @param[in] subsceneName �T�u�V�[����
	* @param[in] entityManager �G���e�B�e�B�}�l�[�W���[
	* @param[in] subsceneData �T�u�V�[�����
	*/
	void SaveSubsceneData(std::string subsceneName, EntityManager* entityManager,
		SubsceneManager::SubsceneData subsceneData);

	/**
	* @brief ���[���h���̃T�u�V�[���̃g�����X�t�H�[�������[�h
	* @param[in] worldName ���[���h��
	*/
	std::unordered_map<std::string, Transform> LoadSubscenesTransform(std::string worldName);
#endif // _DEBUG

};

}// !namespace HaraProject::Framework

#endif // !_EDIT_DATA_MANAGER_H_