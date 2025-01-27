/**
* @file   EditDataUtil.h
* @brief  �ҏW�f�[�^�̓ǂݍ��݁A��������
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
* @brief �n���h�������
* @param[in] entityValueHandler �n���h��
*/
void ReleaceEntityValueHandler(std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler);
//
///**
//* @brief ���[���h��Json�f�[�^���C���X�^���X�����A�T�u�V�[�����ƂɎ擾
//*/
//std::unordered_map<std::string, std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>>>InstantiateWorldJsonForEditor(std::string worldName, bool isAfterPlay = false);
//
///**
//* @brief ���[���h��Json�f�[�^���C���X�^���X�����Ď擾
//* @param[in] worldName ���[���h��
//*/
//std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>>InstantiateWorldJson(std::string worldName);
//
///**
//* @brief �T�u�V�[���̃G���e�B�e�B��Json����C���X�^���X�����Ď擾
//* @param[in] subSceneName �T�u�V�[����
//*/
//std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>>
//InstantiateSubSceneJson(std::string subSceneName, bool isBeforePlay = false);
//
///**
//* @brief ���[���h�̏�Ԃ�Json�t�@�C���ɕۑ�
//* @param[in] editorManager �G�f�B�^�[�}�l�[�W���[
//*/
//void WriteWorldJsonData(EditorManager* editorManager, bool isBeforePlay = false);
//
///**
//* @brief �T�u�V�[���̏�Ԃ�Json�t�@�C���ɕۑ�
//* @param[in] editorManager �G�f�B�^�[�}�l�[�W���[
//* @param[in] subSceneName �T�u�V�[����
//*/
//void WriteSubSceneJsonData(EditorManager* editorManager, std::string subSceneName, bool isBeforePlay = false);
//
///**
//* @brief �T�u�V�[�����Ƃ̃g�����X�t�H�[�����擾
//* @param[in] worldName ���[���h��
//*/
//std::unordered_map<std::string, Transform> ReadSubSubSceneTransforms(std::string worldName);

} // namespace HaraProject::Framework::EditDataUtil

#endif // !_EDIT_DATA_UTIL_H_