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
* @brief ハンドルを解放
* @param[in] entityValueHandler ハンドル
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
//* @brief ワールドのJsonデータをインスタンス化し、サブシーンごとに取得
//*/
//std::unordered_map<std::string, std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>>> InstantiateWorldJsonForEditor(std::string worldName, bool isAfterPlay)
//{
//	std::unordered_map<std::string, std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>>> world_entity_instances{};
//
//	// セーブの用途に応じてパス作成の種類を設定
//	FileType file_type = isAfterPlay ? FileType::BeforePlayData : FileType::WorldData;
//
//	if (!FileExists(file_type, worldName.c_str()))
//	{
//		return world_entity_instances;
//	}
//
//	//--- jsonファイル読み込み
//	std::string path = CreatePath(file_type, worldName.c_str());
//
//	std::ifstream in_file(path);
//	if (in_file.is_open())
//	{
//		// jsonオブジェクトに格納
//		nlohmann::json world_json;
//		in_file >> world_json;
//		in_file.close();
//
//		nlohmann::json subscenes_data = world_json[SUBSCENES_JSON_KEY];
////		nlohmann::json system_data = world_json[SYSTEM_JSON_KEY];
//
//		// サブシーンごとに値を保持したオブジェクトを作成
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
//* @brief ワールドのJsonデータをインスタンス化して取得
//* @param[in] worldName ワールド名
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
//	// jsonファイル読み込み
//	std::string path = CreatePath(FileType::WorldData, worldName.c_str());
//	std::ifstream in_file(path);
//	if (in_file.is_open())
//	{
//		// jsonオブジェクトに格納
//		nlohmann::json world_json;
//		in_file >> world_json;
//		in_file.close();
//
//		nlohmann::json subscenes_data = world_json[SUBSCENES_JSON_KEY];
//
//		// サブシーンごとに値を保持したオブジェクトを作成
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
//* @brief サブシーンのエンティティをJsonからインスタンス化して取得
//* @param[in] subSceneName サブシーン名
//*/
//std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>> InstantiateSubSceneJson(std::string subSceneName, bool isAfterPlay)
//{
//	std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>> subscene_entity_handlers{};
//
//	FileType file_type = isAfterPlay ? FileType::BeforePlayData : FileType::SubSceneData;
//
//	if (!FileExists(file_type, subSceneName.c_str()))return subscene_entity_handlers;
//
//	// ファイル読み込み
//	std::string path = CreatePath(file_type, subSceneName.c_str());
//	std::ifstream in_file(path);
//	if (in_file.is_open())
//	{
//		// jsonオブジェクトに格納
//		nlohmann::json subscene_data;
//		in_file >> subscene_data;
//		in_file.close();
//
//		// エンティティごとにインスタンス化して格納
//		for (const auto& entityData : subscene_data)
//		{
//			std::unordered_map<ComponentBits, ComponentDataBase*> entity_value_hanldler;
//			for (auto component_data = entityData.begin(); component_data != entityData.end(); ++component_data)
//			{
//				// コンポーネント名から識別ビットを取得
//				std::string component_name = component_data.key();
//				ComponentBits mask = ComponentRegistry::GetBitByName(component_name);
//
//				// 識別ビットからインスタンスを作成
//				ComponentDataBase* instance = ComponentRegistry::Constructor(mask);
//				// Jsonデータからインスタンスへ値を設定
//				instance->SetDataFromJson(entityData[component_name]);
//
//				// コンポーネント名とインスタンスをマップへ追加
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
//* @brief ワールドの状態をJsonファイルに保存
//* @param[in] editorManager エディターマネージャー
//*/
//void WriteWorldJsonData(EditorManager* editorManager, bool isBeforePlay)
//{
//	nlohmann::json world_json_data{};
//	nlohmann::json subscene_json_data{};
//
//	//--- ワールドの概要を保存
//	// サブシーンごとのエンティティIDを取得
//	std::unordered_map<std::string, std::vector<uint32_t>> subscene_to_entities = editorManager->GetSubSceneToEntities();
//	std::unordered_map<std::string, Transform> subscene_to_transforms = editorManager->GetSubSceneToTransforms();
//
//	for (const auto& subscene : subscene_to_entities)
//	{
//		// サブシーン名とトランスフォームを記録
////		world_json_data[SUBSCENES_JSON_KEY].push_back(subscene.first);
//		world_json_data[SUBSCENES_JSON_KEY][subscene.first] = subscene_to_transforms[subscene.first].WriteDataToJson();
//	}
//
//	//--- ファイル書き込み
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
//	//--- サブシーン内のエンティティの状態を保存
//	for (const auto& subscene : subscene_to_entities)
//	{
//		// サブシーンごとにセーブ
//		WriteSubSceneJsonData(editorManager, subscene.first, isBeforePlay);
//	}
//}
//
///**
//* @brief サブシーンの状態をJsonファイルに保存
//* @param[in] editorManager エディターマネージャー
//* @param[in] subSceneName サブシーン名
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
//* @brief サブシーンごとのトランスフォームを取得
//* @param[in] worldName ワールド名
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
//	// jsonファイル読み込み
//	std::string path = CreatePath(FileType::WorldData, worldName.c_str());
//	std::ifstream in_file(path);
//	if (in_file.is_open())
//	{
//		// jsonオブジェクトに格納
//		nlohmann::json world_json;
//		in_file >> world_json;
//		in_file.close();
//
//		nlohmann::json subscenes_data = world_json[SUBSCENES_JSON_KEY];
//
//		// サブシーンごとに値を保持したオブジェクトを作成
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