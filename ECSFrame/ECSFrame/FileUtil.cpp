#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

#include "FileUtil.h"

namespace HaraProject::Framework {

/**
* @brief �f�[�^�̎�ނɉ������p�X�𐶐�����
* @param[in] fileType �ǂݍ��ރf�[�^�̎��
* @param[in] key �t�@�C����(�g���q����)
*/
std::string CreatePath(FileType fileType, const char* key)
{
	std::string path;
	switch (fileType)
	{
	case WorldData:
		path = SAVE_DATA_PATH + std::string(WORLD_DATA_PATH) + key + JSON_EXTENSION;
		break;
	case SubSceneData:
		path = SAVE_DATA_PATH + std::string(SUBSCENE_DATA_PATH) + key + JSON_EXTENSION;
		break;
	case BeginWorldData:
		path = std::string(SAVE_DATA_PATH) + key + JSON_EXTENSION;
		break;
	case ShaderBinary:
		path = ASSETS_DATA_PATH + std::string(SHADER_DATA_PATH) + key + ".cso";
		break;
	case ModelData:
		path = ASSETS_DATA_PATH + std::string(MODEL_DATA_PATH) + key;
		break;
	case UITexture:
		path = ASSETS_DATA_PATH + std::string(UITEXTURE_DATA_PATH) + key;
		break;
	case SoundSE:
		path = "Assets/SE/" + std::string(key);
		break;
	case SoundBGM:
		path = "Assets/BGM/" + std::string(key);
		break;
	}
	return path;
}

/**
* @brief �t�@�C�������݂��邩�m�F
* @param[in] fileType �ǂݍ��ރf�[�^�̎��
* @param[in] key �t�@�C����(�g���q����)
*/
bool FileExists(FileType fileType, const char* key)
{
	return std::filesystem::exists(CreatePath(fileType, key));
}

/**
* @brief �p�X���K�w���Ƃɕ������Ĕz��ŕԂ�
* @param[in] path �p�X
*/
std::vector<std::string> SplitPath(std::string path)
{
	std::vector<std::string> parts;
	std::stringstream ss(path);
	std::string part;

	while (std::getline(ss, part, '/')) {
		parts.push_back(part);
	}
	return parts;
}
}// namespace HaraProject::Framework