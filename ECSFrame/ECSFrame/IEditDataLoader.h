/**
* @file   IEditDataLoader.h
* @brief  �ҏW�f�[�^���[�h�p�C���^�[�t�F�[�X.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _IEDIT_DATA_LOADER_H_
#define _IEDIT_DATA_LOADER_H_

#include <string>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "EntityTypes.h"
#include "SoundManager.h"

namespace HaraProject::Framework {

class IEditDataLoader
{
public:
	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~IEditDataLoader() = default;

	/**
	* @brief ���[���h���̑S�G���e�B�e�B�f�[�^�����[�h
	* @param[in] worldName ���[���h��
	*/
	virtual EntityDataList LoadWorldData(std::string worldName) = 0;

	/**
	* @brief �T�u�V�[�����̑S�G���e�B�e�B�f�[�^�����[�h
	* @param[in] subsceneName �T�u�V�[����
	*/
	virtual EntityDataList LoadSubSceneData(std::string subsceneName) = 0;

	/**
	* @brief ���[���h�Ŏg�p����T�E���h�ꗗ���擾
	* @param[in] worldName ���[���h��
	*/
	virtual std::unordered_map<SoundManager::SoundType, std::vector<std::string>> LoadSoundNames(std::string worldName) = 0;

	/**
	* @brief �ǂݍ��݂Ŏg�����G���e�B�e�B�̃f�[�^���������
	* @param[in] loadedEntityData �g���I������G���e�B�e�B�f�[�^
	*/
	virtual void ReleaceLoadedEntityData(EntityData loadedEntityData) = 0;
};

}// !namespace HaraProject::Framework

#endif // !_IEDIT_DATA_LOADER_H_