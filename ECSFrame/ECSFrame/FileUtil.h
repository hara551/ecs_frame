/**
* @file   FileUtil.h
* @brief  ファイル関連操作関数まとめ.
* @author Hara Sota.
* @date   2024/10/26
*/
#ifndef _FILE_UTIL_H_
#define _FILE_UTIL_H_

#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

namespace HaraProject::Framework {

// パス
static const char* SAVE_DATA_PATH = "Saves/";
static const char* ASSETS_DATA_PATH = "Assets/";

static const char* WORLD_DATA_PATH = "World/";
static const char* SUBSCENE_DATA_PATH = "SubScene/";
static const char* BEFORE_PLAY_WORLD_DATA_PATH = "BeforePlay/";
static const char* MODEL_DATA_PATH = "Model/";
static const char* SHADER_DATA_PATH = "Shader/";
static const char* UITEXTURE_DATA_PATH = "UITexture/";

// 拡張子
static const std::string JSON_EXTENSION = ".json";

/**
* @brief データの種類
*/
enum FileType
{
	WorldData = 0,
	SubSceneData,
	BeginWorldData,
	ShaderBinary,
	ModelData,
	UITexture,
	SoundSE,
	SoundBGM
};

/**
* @brief データの種類に応じたパスを生成する
* @param[in] fileType 読み込むデータの種類
* @param[in] key ファイル名(拡張子抜き)
*/
std::string CreatePath(FileType fileType, const char* key);

/**
* @brief ファイルが存在するか確認
* @param[in] fileType 読み込むデータの種類
* @param[in] key ファイル名(拡張子抜き)
*/
bool FileExists(FileType fileType, const char* key);

/**
* @brief パスを階層ごとに分割して配列で返す
* @param[in] path パス
*/
std::vector<std::string> SplitPath(std::string path);

}// namespace HaraProject::Framework
#endif // !_FILE_UTIL_H_