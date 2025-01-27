/**
* @file   EditDataUtil.h
* @brief  編集データの読み込み、書き込み
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _EDIT_DATA_UTIL_H_
#define _EDIT_DATA_UTIL_H_

#include <map>
#include <string>
#include <memory>

#include "ComponentDataBase.h"
#include "ComponentMask.h"
#include "SystemBase.h"
#include "SystemMask.h"
#include "SystemManager.h"

#include "EntityValueHandler.h"
#include "SystemManager.h"
#include "EditorManager.h"
#include "Transform.h"

namespace HaraProject::Framework {

/**
* @brief ハンドルを解放
* @param[in] entityValueHandler ハンドル
*/
void ReleaceEntityValueHandler(std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler);
//
///**
//* @brief ワールドのJsonデータをインスタンス化し、サブシーンごとに取得
//*/
//std::unordered_map<std::string, std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>>>InstantiateWorldJsonForEditor(std::string worldName, bool isAfterPlay = false);
//
///**
//* @brief ワールドのJsonデータをインスタンス化して取得
//* @param[in] worldName ワールド名
//*/
//std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>>InstantiateWorldJson(std::string worldName);
//
///**
//* @brief サブシーンのエンティティをJsonからインスタンス化して取得
//* @param[in] subSceneName サブシーン名
//*/
//std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>>
//InstantiateSubSceneJson(std::string subSceneName, bool isBeforePlay = false);
//
///**
//* @brief ワールドの状態をJsonファイルに保存
//* @param[in] editorManager エディターマネージャー
//*/
//void WriteWorldJsonData(EditorManager* editorManager, bool isBeforePlay = false);
//
///**
//* @brief サブシーンの状態をJsonファイルに保存
//* @param[in] editorManager エディターマネージャー
//* @param[in] subSceneName サブシーン名
//*/
//void WriteSubSceneJsonData(EditorManager* editorManager, std::string subSceneName, bool isBeforePlay = false);
//
///**
//* @brief サブシーンごとのトランスフォームを取得
//* @param[in] worldName ワールド名
//*/
//std::unordered_map<std::string, Transform> ReadSubSubSceneTransforms(std::string worldName);

} // namespace HaraProject::Framework::EditDataUtil

#endif // !_EDIT_DATA_UTIL_H_