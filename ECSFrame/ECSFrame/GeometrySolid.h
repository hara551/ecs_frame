/**
* @file   GeometrySolid.h
* @brief  幾何立体コンポーネントデータ.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _GEOMETRY_SOLID_H_
#define _GEOMETRY_SOLID_H_

#include <DirectXMath.h>

#include <memory>

#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiTreeNode.h"
#include "GuiInputFloat3.h"
#endif // _DEBUG

#include "MathUtil.h"
#include "ComponentDataBase.h"

namespace HaraProject::Framework {

class GeometrySolid : public ComponentDataBase
{
public:
	/**
	* @brief データ名
	*/
	static constexpr const char* GEOMETRY_SOLID_NAME = "GeometrySolid";
	static constexpr const char* GEOMETRY_SOLID_GEOMETRY_NUM = "geometryNum";
	static constexpr const char* GEOMETRY_SOLID_COLOR_NAME = "color";

	/**
	* @brief コンストラクタ
	*/
	GeometrySolid();

	/**
	* @brief コピーコンストラクタ
	* @param[in] base GeometrySolidが入った基底クラスポインタ
	*/
	GeometrySolid(ComponentDataBase* base);

	/**
	* @brief デストラクタ
	*/
	~GeometrySolid() = default;

	/**
	* @brief Jsonデータから値を設定する
	* @param[in] json jsonオブジェクト
	*/
	void SetDataFromJson(nlohmann::json jsonData)override;

	/**
	* @brief 立体番号
	*/
	int geometryNum;

	/**
	* @breif 描画色
	*/
	DirectX::XMFLOAT4 color;

#ifdef _DEBUG
	/**
	* @brief 現在の値をJsonデータに変換する
	*/
	nlohmann::json WriteDataToJson()override
	{
		nlohmann::json jsonData;

		jsonData[GEOMETRY_SOLID_NAME][GEOMETRY_SOLID_GEOMETRY_NUM] = geometryNum;
		jsonData[GEOMETRY_SOLID_NAME][GEOMETRY_SOLID_COLOR_NAME] = { color.x,color.y,color.z,color.w };

		return jsonData;
	}

	/**
	* @brief インスペクタ―表示作成
	*/
	GuiItemBase* CreateDetailContent(GuiManager* guiManager)override
	{
		GuiTreeNode* gui = guiManager->CreateGuiTreeNode(GEOMETRY_SOLID_NAME, "id");
		gui->AddChildren(
			guiManager->CreateGuiInputInt(GEOMETRY_SOLID_GEOMETRY_NUM, "id", &geometryNum),
			guiManager->CreateGuiInputColor(GEOMETRY_SOLID_COLOR_NAME, "id", &color)
		);
		return gui;
	};
#endif // _DEBUG
};

}// !namespace HaraProject::Framework

#endif // !_GEOMETRY_SOLID_H_