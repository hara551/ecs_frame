/**
* @file   EntityTypes.h
* @brief  エンティティのデータを扱う際の単位型定義.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _ENTITY_TYPES_H_
#define _ENTITY_TYPES_H_

#include <vector>
#include <unordered_map>

#include "ComponentMask.h"
#include "ComponentDataBase.h"

namespace HaraProject::Framework {

/**
* @brief エンティティをコンポーネントの塊として扱う際の単位型
*/
using EntityData = std::unordered_map<ComponentBits, ComponentDataBase*>;

/**
* @brief EntityDataの配列
*/
using EntityDataList = std::vector<EntityData>;

}// !namespace HaraProject::Framework

#endif // !_ENTITY_TYPES_H_