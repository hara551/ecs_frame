
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
* @brief Jsonファイル内でのサブシーン一覧ブロックのキー
*/
static const char* SUBSCENES_JSON_KEY = "SubScenes";

/**
* @brief Jsonファイル内でのサウンド一覧ブロックのキー
*/
static const char* SOUNDS_JSON_KEY = "Sounds";

/**
* @brief Jsonファイル書き出し時の要素ごとのインデント数
*/
static const uint8_t JSON_DUMP_NUM = 4;

/**
* @brief ワールドの全エンティティデータをロード
* @param[in] worldName ワールド名
*/
EntityDataList EditDataManager::LoadWorldData(std::string worldName)
{
	EntityDataList world_entity_datas{};

	// ファイルが存在しなければ空で返す
	FileType world_data_type = FileType::WorldData;
	if (!FileExists(world_data_type, worldName.c_str()))
	{
		return world_entity_datas;
	}

	std::string path = CreatePath(world_data_type, worldName.c_str());

	nlohmann::json world_json = ReadJsonFile(path);

	// 項目ごとに取得
	nlohmann::json subscenes_json = world_json[SUBSCENES_JSON_KEY];

	for (auto subscene_json = subscenes_json.begin(); subscene_json != subscenes_json.end(); ++subscene_json)
	{
		// サブシーンごとにエンティティの値をロード
		std::string subscene_name = subscene_json.key();
		EntityDataList subscene_entitiy_datas = LoadSubSceneData(subscene_name);
		// 結果に追加
		world_entity_datas.insert(world_entity_datas.end(), 
			subscene_entitiy_datas.begin(), subscene_entitiy_datas.end());
	}
	return world_entity_datas;
}

/**
* @brief サブシーン内の全エンティティデータをロード
* @param[in] subsceneName サブシーン名
*/
EntityDataList EditDataManager::LoadSubSceneData(std::string subsceneName)
{
	EntityDataList subscene_entity_datas{};

	// ファイルが存在しなければ空で返す
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
			// コンポーネント名から識別ビットを取得
			std::string component_name = component_json.key();
			ComponentBits component_bit = ComponentRegistry::GetBitByName(component_name);

			// 識別ビットからコンストラクタを実行
			ComponentDataBase* component_data = ComponentRegistry::Constructor(component_bit);
			// jsonからコンポーネントに値を設定
			component_data->SetDataFromJson(entity_json[component_name]);

			// コンポーネントをエンティティデータに追加
			entity_data.emplace(component_bit, component_data);
		}
		// 結果に追加
		subscene_entity_datas.push_back(entity_data);
	}
	return subscene_entity_datas;
}

/**
* @brief 読み込みで使ったエンティティのデータを解放する
* @param[in] loadedEntityData 使い終わったエンティティデータ
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
* @brief ワールドで使用するサウンド一覧を取得
* @param[in] worldName ワールド名
*/
std::unordered_map<SoundManager::SoundType, std::vector<std::string>> EditDataManager::LoadSoundNames(std::string worldName)
{
	std::unordered_map<SoundManager::SoundType, std::vector<std::string>> world_sound_names{};

	// ファイルが存在しなければ空で返す
	FileType world_data_type = FileType::WorldData;
	if (!FileExists(world_data_type, worldName.c_str()))
	{
		return world_sound_names;
	}

	std::string path = CreatePath(world_data_type, worldName.c_str());

	nlohmann::json world_json = ReadJsonFile(path);
	// サウンド一覧のブロックを抽出
	if (!world_json.contains(SOUNDS_JSON_KEY))
	{
		return world_sound_names; // サウンド情報がない場合は空で返す
	}

	nlohmann::json sounds_json = world_json[SOUNDS_JSON_KEY];

	// サウンドの種類（SE, BGM）をループ処理
	for (const auto& [sound_type, sound_list] : sounds_json.items())
	{
		SoundManager::SoundType type;

		// サウンドタイプを判定
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
			continue; // SE, BGM以外のキーはスキップ
		}

		// サウンドファイル名を取得
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
* @brief ゲームの最初にロードするワールド名を取得
*/
std::string EditDataManager::LoadBeginningWorldName()
{
	// ファイルが存在しなければ空で返す
	if (!FileExists(FileType::BeginWorldData, "Initialize"))return std::string();
	
	// パス作成
	std::string path = CreatePath(FileType::BeginWorldData, "Initialize");
	
	// 読み込み
	nlohmann::json initialize_json = ReadJsonFile(path);

	// 最初にロードするワールド名を取得
	std::string beginning_world_name = initialize_json[0].get<std::string>();
	return beginning_world_name;
}

/**
* @brief Jsonファイルの読み取り
* @param[in] path ファイルパス
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
* @brief Jsonファイルの書き出し
* @param[in] path ファイルパス
* @param[in] jsonData 書き出すJsonオブジェクト
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
* @brief ワールド内のエンティティデータをサブシーンごとにをロード
* @param[in] worldName ワールド名
*/
std::unordered_map<std::string, EntityDataList> EditDataManager::LoadWorldDataForEditor(std::string worldName)
{
	std::unordered_map<std::string, EntityDataList> world_entity_datas{};

	// ファイルが存在しなければ空で返す
	FileType world_data_type = FileType::WorldData;
	if (!FileExists(world_data_type, worldName.c_str()))
	{
		return world_entity_datas;
	}

	std::string path = CreatePath(world_data_type, worldName.c_str());

	nlohmann::json world_json = ReadJsonFile(path);

	// サブシーン一覧のブロックを抽出
	nlohmann::json subscenes_json = world_json[SUBSCENES_JSON_KEY];

	for (auto subscene_json = subscenes_json.begin(); subscene_json != subscenes_json.end(); ++subscene_json)
	{
		// サブシーンごとにエンティティの値をロード
		std::string subscene_name = subscene_json.key();
		EntityDataList subscene_entity_datas = LoadSubSceneData(subscene_name);

		// 結果に追加
		world_entity_datas.emplace(subscene_name, subscene_entity_datas);
	}
	return world_entity_datas;
}

/**
* @brief ワールド内のサブシーンのトランスフォームをロード
* @param[in] worldName ワールド名
*/
std::unordered_map<std::string, Transform> EditDataManager::LoadSubscenesTransform(std::string worldName)
{
	std::unordered_map<std::string, Transform> subscene_to_transform{};

	// ファイルが存在しなければ空で返す
	FileType world_data_type = FileType::WorldData;
	if (!FileExists(world_data_type, worldName.c_str()))
	{
		return subscene_to_transform;
	}

	std::string path = CreatePath(world_data_type, worldName.c_str());

	nlohmann::json world_json = ReadJsonFile(path);

	// サブシーン一覧のブロックを抽出
	nlohmann::json subscenes_json = world_json[SUBSCENES_JSON_KEY];

	for (auto subscene_json = subscenes_json.begin(); subscene_json != subscenes_json.end(); ++subscene_json)
	{
		// サブシーンのトランスフォームを取得
		std::string subscene_name = subscene_json.key();
		Transform transform{};
		transform.SetDataFromJson(subscene_json.value()[Transform::TRANSFORM_NAME]);

		// 結果に追加
		subscene_to_transform.emplace(subscene_name, transform);
	}
	return subscene_to_transform;
}

/**
* @brief ワールドデータをJsonに保存
* @param[in] worldName ワールド名
* @param[in] entityManager エンティティマネージャー
* @param[in] subsceneDatas サブシーン情報リスト
*/
void EditDataManager::SaveWorldData(std::string worldName, EntityManager* entityManager,
	std::unordered_map<std::string, SubsceneManager::SubsceneData> subsceneDatas)
{
	nlohmann::json world_json{};
	for (auto& [subscene_name, subscene_data] : subsceneDatas)
	{
		// サブシーン名とトランスフォームをJsonオブジェクトに格納
		world_json[SUBSCENES_JSON_KEY][subscene_name] = subscene_data.transform.WriteDataToJson();

		// サブシーン内のエンティティの状態を保存
		SaveSubsceneData(subscene_name, entityManager, subscene_data);
	}
	// サブシーン名とトランスフォームをJsonファイルに書き出す
	std::string path = CreatePath(FileType::WorldData, worldName.c_str());
	WriteJsonFile(path, world_json);
}

/**
* @brief サブシーンデータをJsonに保存
* @param[in] subsceneName サブシーン名
* @param[in] entityManager エンティティマネージャー
* @param[in] subsceneData サブシーン情報
*/
void EditDataManager::SaveSubsceneData(std::string subsceneName, EntityManager* entityManager, SubsceneManager::SubsceneData subsceneData)
{
	nlohmann::json subscene_json{};
	for (const auto& entity : subsceneData.entities)
	{
		// エンティティのデータをJsonオブジェクトに格納
		subscene_json.push_back(entityManager->ConvertEntityToJson(entity));
	}
	// サブシーン内のエンティティのデータをJsonファイルに書き出す
	std::string path = CreatePath(FileType::SubSceneData, subsceneName.c_str());
	WriteJsonFile(path, subscene_json);
}
#endif // _DEBUG


}// !namespace HaraProject::Framework