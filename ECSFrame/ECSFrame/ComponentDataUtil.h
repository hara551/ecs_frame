/**
* @file   ComponentDataUtil.h
* @brief  �R���|�[�l���g�f�[�^�֗��֐��܂Ƃ�.
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
* @brief �K�v�ȃ��f���f�[�^�̖��O���擾
* @param[in] componentDataManager �R���|�[�l���g�f�[�^�}�l�[�W���[
*/
std::set<std::string> GetNeedsModelNames(ComponentDataManager* componentDataManager);

/**
* @brief �K�v�ȃe�N�X�`���̖��O���擾
* @param[in] componentDataManager �R���|�[�l���g�f�[�^�}�l�[�W���[
*/
std::set<std::string> GetNeedsTextureNames(ComponentDataManager* componentDataManager);

}// namespace HaraProject::Framework

#endif // !_COMPONENT_DATA_UTIL_H_