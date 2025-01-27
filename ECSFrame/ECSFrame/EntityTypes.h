/**
* @file   EntityTypes.h
* @brief  �G���e�B�e�B�̃f�[�^�������ۂ̒P�ʌ^��`.
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
* @brief �G���e�B�e�B���R���|�[�l���g�̉�Ƃ��Ĉ����ۂ̒P�ʌ^
*/
using EntityData = std::unordered_map<ComponentBits, ComponentDataBase*>;

/**
* @brief EntityData�̔z��
*/
using EntityDataList = std::vector<EntityData>;

}// !namespace HaraProject::Framework

#endif // !_ENTITY_TYPES_H_