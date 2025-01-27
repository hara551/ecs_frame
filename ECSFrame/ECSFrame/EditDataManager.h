/**
* @file   EditDataManager.h
* @brief  編集データ管理.
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
	* @brief コンストラクタ
	*/
	EditDataManager() = default;

	/**
	* @brief デストラクタ
	*/
	~EditDataManager() = default;

	/**
	* @brief ワールド内の全エンティティデータをロード
	* @param[in] worldName ワールド名
	*/
	EntityDataList LoadWorldData(std::string worldName)override;

	/**
	* @brief サブシーン内の全エンティティデータをロード
	* @param[in] subsceneName サブシーン名
	*/
	EntityDataList LoadSubSceneData(std::string subsceneName)override;

	/**
	* @brief 読み込みで使ったエンティティのデータを解放する
	* @param[in] loadedEntityData 使い終わったエンティティデータ
	*/
	void ReleaceLoadedEntityData(EntityData loadedEntityData)override;

	/**
	* @brief ワールドで使用するサウンド一覧を取得
	* @param[in] worldName ワールド名
	*/
	std::unordered_map<SoundManager::SoundType, std::vector<std::string>> LoadSoundNames(std::string worldName)override;

	/**
	* @brief ゲームの最初にロードするワールド名を取得
	*/
	std::string LoadBeginningWorldName();

	/**
	* @brief Jsonファイルの読み取り
	* @param[in] path ファイルパス
	*/
	nlohmann::json ReadJsonFile(std::string path);

	/**
	* @brief Jsonファイルの書き出し
	* @param[in] path ファイルパス
	* @param[in] jsonData 書き出すJsonオブジェクト
	*/
	void WriteJsonFile(std::string path, nlohmann::json jsonData);

#ifdef _DEBUG

	/**
	* @brief ワールド内のエンティティデータをサブシーンごとにをロード
	* @param[in] worldName ワールド名
	*/
	std::unordered_map<std::string, EntityDataList> LoadWorldDataForEditor(std::string worldName);

	/**
	* @brief ワールドデータをJsonに保存
	* @param[in] worldName ワールド名
	* @param[in] entityManager エンティティマネージャー
	* @param[in] subsceneDatas サブシーン情報リスト
	*/
	void SaveWorldData(std::string worldName, EntityManager* entityManager,
		std::unordered_map<std::string, SubsceneManager::SubsceneData> subsceneDatas);

	/**
	* @brief サブシーンデータをJsonに保存
	* @param[in] subsceneName サブシーン名
	* @param[in] entityManager エンティティマネージャー
	* @param[in] subsceneData サブシーン情報
	*/
	void SaveSubsceneData(std::string subsceneName, EntityManager* entityManager,
		SubsceneManager::SubsceneData subsceneData);

	/**
	* @brief ワールド内のサブシーンのトランスフォームをロード
	* @param[in] worldName ワールド名
	*/
	std::unordered_map<std::string, Transform> LoadSubscenesTransform(std::string worldName);
#endif // _DEBUG

};

}// !namespace HaraProject::Framework

#endif // !_EDIT_DATA_MANAGER_H_