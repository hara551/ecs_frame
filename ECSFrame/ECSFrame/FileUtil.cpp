#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

#include "FileUtil.h"

namespace HaraProject::Framework {

/**
* @brief データの種類に応じたパスを生成する
* @param[in] fileType 読み込むデータの種類
* @param[in] key ファイル名(拡張子抜き)
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
* @brief ファイルが存在するか確認
* @param[in] fileType 読み込むデータの種類
* @param[in] key ファイル名(拡張子抜き)
*/
bool FileExists(FileType fileType, const char* key)
{
	return std::filesystem::exists(CreatePath(fileType, key));
}

/**
* @brief パスを階層ごとに分割して配列で返す
* @param[in] path パス
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