/**
* @file   EntityName.h
* @brief  エンティティ名コンポーネントデータ定義.
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
* @brief エンティティ名コンポーネントデータ
*/
class EntityName : public ComponentDataBase
{
public:
	/**
	* @brief データ名
	*/
	static constexpr const char* ENTITY_NAME_NAME = "EntityName";
	static constexpr const char* ENTITY_NAME_NAME_NAME = "name";

	/**
	* @brief デフォルトコンストラクタ
	*/
	EntityName() : name("unknown") {};

	/**
	* @brief コピーコンストラクタ
	* @param[in] base EntityNameが入った基底クラスポインタ
	*/
	EntityName(ComponentDataBase* base)
		//: name("unknown")
	{
		EntityName* value = dynamic_cast<EntityName*>(base);
		strcpy_s(name,value->name);
	}

	/**
	* @brief Jsonデータから値を設定する
	* @param[in] json jsonオブジェクト
	*/
	void SetDataFromJson(nlohmann::json jsonData)override
	{
		strcpy_s(name, std::string(jsonData[ENTITY_NAME_NAME_NAME]).c_str());
	}

#ifdef _DEBUG
	/**
	* @brief 現在の値をJsonデータに変換する
	*/
	nlohmann::json WriteDataToJson()override
	{
		nlohmann::json jsonData;

		jsonData[ENTITY_NAME_NAME][ENTITY_NAME_NAME_NAME] = std::string(name);

		return jsonData;
	}

	/**
	* @brief インスペクタ―表示作成
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
	* @brief エンティティ名
	*/
	char name[GuiInputText::MAX_INPUT_TEXT_LENGTH];// TODO:サイズ定義場所を検討
};

}

#endif // !_ENTITY_NAME_H_
