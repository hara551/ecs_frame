/**
* @file   ComponentDataBase.h
* @brief  �R���|�[�l���g�f�[�^���N���X��`.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _COMPONENT_DATA_BASE_H_
#define _COMPONENT_DATA_BASE_H_

#include <memory>

#include "nlohmann/json.hpp"

#ifdef _DEBUG
#include "GuiItemBase.h"
#include "GuiManager.h"
#endif // _DEBUG

namespace HaraProject::Framework
{

/**
* @brief �R���|�[�l���g�f�[�^���
*/
class ComponentDataBase
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	ComponentDataBase() = default;

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~ComponentDataBase() = default;

	/**
	* @brief �f�[�^������
	*/
	void Disable() { isAble = false; }

	/**
	* @brief �f�[�^���L����
	*/
	bool IsAble() { return isAble; }

	/**
	* @brief Json�f�[�^����l��ݒ肷��
	* @param[in] json json�I�u�W�F�N�g
	*/
	virtual void SetDataFromJson(nlohmann::json json) = 0;

#ifdef _DEBUG
	/**
	* @brief ���݂̒l��Json�f�[�^�ɕϊ�����
	*/
	virtual nlohmann::json WriteDataToJson() { return nlohmann::json(); };

	/**
	* @brief �C���X�y�N�^�\�\���쐬
	*/
	virtual GuiItemBase* CreateDetailContent(GuiManager* guiManager) { return nullptr; }
#endif // _DEBUG

protected:
	/**
	* @brief �f�[�^�L���t���O
	*/
	bool isAble = true;;
};

}

#endif // !_COMPONENT_DATA_BASE_H_
