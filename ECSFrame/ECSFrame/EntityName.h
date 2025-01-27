/**
* @file   EntityName.h
* @brief  �G���e�B�e�B���R���|�[�l���g�f�[�^��`.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _ENTITY_NAME_H_
#define _ENTITY_NAME_H_

#include <DirectXMath.h>

#include <memory>

#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiTreeNode.h"
#include "DetailsWindow.h"
#endif // _DEBUG
#include "GuiInputText.h"

#include "ComponentDataBase.h"

namespace HaraProject::Framework
{

/**
* @brief �G���e�B�e�B���R���|�[�l���g�f�[�^
*/
class EntityName : public ComponentDataBase
{
public:
	/**
	* @brief �f�[�^��
	*/
	static constexpr const char* ENTITY_NAME_NAME = "EntityName";
	static constexpr const char* ENTITY_NAME_NAME_NAME = "name";

	/**
	* @brief �f�t�H���g�R���X�g���N�^
	*/
	EntityName() : name("unknown") {};

	/**
	* @brief �R�s�[�R���X�g���N�^
	* @param[in] base EntityName�����������N���X�|�C���^
	*/
	EntityName(ComponentDataBase* base)
		//: name("unknown")
	{
		EntityName* value = dynamic_cast<EntityName*>(base);
		strcpy_s(name,value->name);
	}

	/**
	* @brief Json�f�[�^����l��ݒ肷��
	* @param[in] json json�I�u�W�F�N�g
	*/
	void SetDataFromJson(nlohmann::json jsonData)override
	{
		strcpy_s(name, std::string(jsonData[ENTITY_NAME_NAME_NAME]).c_str());
	}

#ifdef _DEBUG
	/**
	* @brief ���݂̒l��Json�f�[�^�ɕϊ�����
	*/
	nlohmann::json WriteDataToJson()override
	{
		nlohmann::json jsonData;

		jsonData[ENTITY_NAME_NAME][ENTITY_NAME_NAME_NAME] = std::string(name);

		return jsonData;
	}

	/**
	* @brief �C���X�y�N�^�\�\���쐬
	*/
	GuiItemBase* CreateDetailContent(GuiManager* guiManager)override
	{
		GuiTreeNode* entity_name_gui = guiManager->CreateGuiTreeNode(ENTITY_NAME_NAME, "id");
		entity_name_gui->AddChildren(
			guiManager->CreateGuiInputText(ENTITY_NAME_NAME_NAME, "id", GuiInputBase::Return, name)
		);
		return entity_name_gui;
	};
#endif // _DEBUG

	/**
	* @brief �G���e�B�e�B��
	*/
	char name[GuiInputText::MAX_INPUT_TEXT_LENGTH];// TODO:�T�C�Y��`�ꏊ������
};

}

#endif // !_ENTITY_NAME_H_
