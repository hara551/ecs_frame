/**
* @file   ModelHandle.h
* @brief  ���f���R���|�[�l���g�f�[�^.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _MODEL_HANDLE_H_
#define _MODEL_HANDLE_H_

#include <DirectXMath.h>

#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiTreeNode.h"
#include "GuiInputFloat2.h"
#include "GuiInputColor.h"
#endif // _DEBUG
#include "GuiInputText.h"

#include "Defines.h"

#include "Model.h"
#include "ComponentDataBase.h"

namespace HaraProject::Framework
{

/**
* @brief �ʒu�A��]�A�g�k�R���|�[�l���g�f�[�^
*/
class ModelHandle : public ComponentDataBase
{
public:
	/**
	* @brief �f�[�^��
	*/
	static constexpr const char* MODEL_HANDLE_NAME = "ModelHandle";
	static constexpr const char* MODEL_HANDLE_MODEL_NAME_NAME = "modelName";

	/**
	* @brief �R���X�g���N�^
	*/
	ModelHandle()
		: model(nullptr)
		, modelName("nothing")
	{}

	/**
	* @brief �R�s�[�R���X�g���N�^
	* @param[in] base �l�����������N���X�|�C���^
	*/
	ModelHandle(ComponentDataBase* base)
	{
		ModelHandle* value = dynamic_cast<ModelHandle*>(base);
		strcpy_s(modelName, value->modelName);
		model = nullptr;
	}

	/**
	* @brief Json�f�[�^����l��ݒ肷��
	* @param[in] json json�I�u�W�F�N�g
	*/
	void SetDataFromJson(nlohmann::json jsonData)override
	{
		strcpy_s(modelName, std::string(jsonData[MODEL_HANDLE_MODEL_NAME_NAME]).c_str());
	}

#ifdef _DEBUG
	/**
	* @brief ���݂̒l��Json�f�[�^�ɕϊ�����
	*/
	nlohmann::json WriteDataToJson()override
	{
		nlohmann::json jsonData;

		jsonData[MODEL_HANDLE_NAME][MODEL_HANDLE_MODEL_NAME_NAME] = std::string(modelName);

		return jsonData;
	}

	/**
	* @brief �C���X�y�N�^�\�\���쐬
	*/
	GuiItemBase* CreateDetailContent(GuiManager* guiManager)override
	{
		GuiTreeNode* model_handle_gui = guiManager->CreateGuiTreeNode(MODEL_HANDLE_NAME, "id");
		model_handle_gui->AddChildren(
			guiManager->CreateGuiInputText(MODEL_HANDLE_MODEL_NAME_NAME, "id", GuiInputBase::Return, modelName)
		);
		return model_handle_gui;
	};
#endif // _DEBUG

	/**
	* @brief ���f���t�@�C����
	*/
	char modelName[GuiInputText::MAX_INPUT_TEXT_LENGTH];

	/**
	* @brief ���f���f�[�^
	*/
	Model* model;
};

}// !namespace HaraProject::Framework

#endif // !_MODEL_HANDLE_H_