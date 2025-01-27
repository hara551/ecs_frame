/**
* @file   ModelHandle.h
* @brief  モデルコンポーネントデータ.
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
* @brief 位置、回転、拡縮コンポーネントデータ
*/
class ModelHandle : public ComponentDataBase
{
public:
	/**
	* @brief データ名
	*/
	static constexpr const char* MODEL_HANDLE_NAME = "ModelHandle";
	static constexpr const char* MODEL_HANDLE_MODEL_NAME_NAME = "modelName";

	/**
	* @brief コンストラクタ
	*/
	ModelHandle()
		: model(nullptr)
		, modelName("nothing")
	{}

	/**
	* @brief コピーコンストラクタ
	* @param[in] base 値が入った基底クラスポインタ
	*/
	ModelHandle(ComponentDataBase* base)
	{
		ModelHandle* value = dynamic_cast<ModelHandle*>(base);
		strcpy_s(modelName, value->modelName);
		model = nullptr;
	}

	/**
	* @brief Jsonデータから値を設定する
	* @param[in] json jsonオブジェクト
	*/
	void SetDataFromJson(nlohmann::json jsonData)override
	{
		strcpy_s(modelName, std::string(jsonData[MODEL_HANDLE_MODEL_NAME_NAME]).c_str());
	}

#ifdef _DEBUG
	/**
	* @brief 現在の値をJsonデータに変換する
	*/
	nlohmann::json WriteDataToJson()override
	{
		nlohmann::json jsonData;

		jsonData[MODEL_HANDLE_NAME][MODEL_HANDLE_MODEL_NAME_NAME] = std::string(modelName);

		return jsonData;
	}

	/**
	* @brief インスペクタ―表示作成
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
	* @brief モデルファイル名
	*/
	char modelName[GuiInputText::MAX_INPUT_TEXT_LENGTH];

	/**
	* @brief モデルデータ
	*/
	Model* model;
};

}// !namespace HaraProject::Framework

#endif // !_MODEL_HANDLE_H_