/**
* @file   IEditDataLoader.h
* @brief  編集データロード用インターフェース.
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
	* @brief デストラクタ
	*/
	virtual ~IEditDataLoader() = default;

	/**
	* @brief ワールド内の全エンティティデータをロード
	* @param[in] worldName ワールド名
	*/
	virtual EntityDataList LoadWorldData(std::string worldName) = 0;

	/**
	* @brief サブシーン内の全エンティティデータをロード
	* @param[in] subsceneName サブシーン名
	*/
	virtual EntityDataList LoadSubSceneData(std::string subsceneName) = 0;

	/**
	* @brief ワールドで使用するサウンド一覧を取得
	* @param[in] worldName ワールド名
	*/
	virtual std::unordered_map<SoundManager::SoundType, std::vector<std::string>> LoadSoundNames(std::string worldName) = 0;

	/**
	* @brief 読み込みで使ったエンティティのデータを解放する
	* @param[in] loadedEntityData 使い終わったエンティティデータ
	*/
	virtual void ReleaceLoadedEntityData(EntityData loadedEntityData) = 0;
};

}// !namespace HaraProject::Framework

#endif // !_IEDIT_DATA_LOADER_H_