/**
* @file   ComponentDataUtil.h
* @brief  コンポーネントデータ便利関数まとめ.
* @author Hara Sota.
* @date   2024/10/07
*/
#ifndef _COMPONENT_DATA_UTIL_H_
#define _COMPONENT_DATA_UTIL_H_

#include <string>
#include <vector>
#include <set>

#include "ComponentDataManager.h"

namespace HaraProject::Framework {

/**
* @brief 必要なモデルデータの名前を取得
* @param[in] componentDataManager コンポーネントデータマネージャー
*/
std::set<std::string> GetNeedsModelNames(ComponentDataManager* componentDataManager);

/**
* @brief 必要なテクスチャの名前を取得
* @param[in] componentDataManager コンポーネントデータマネージャー
*/
std::set<std::string> GetNeedsTextureNames(ComponentDataManager* componentDataManager);

}// namespace HaraProject::Framework

#endif // !_COMPONENT_DATA_UTIL_H_