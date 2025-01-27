/**
* @file   CollisionCircle2D.h
* @brief　2D当たり判定用サークル
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _COLLISION_CIRCLE_2D_H_
#define _COLLISION_CIRCLE_2D_H_

#include <DirectXMath.h>

#include <memory>

#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiTreeNode.h"
#include "GuiInputFloat3.h"
#endif // _DEBUG

#include "ComponentDataBase.h"

namespace HaraProject::Framework
{

class CollisionCircle2D : public ComponentDataBase
{
public:
	/**
	* @brief データ名
	*/
	static constexpr const char* COLLISION_CIRCLE_2D_NAME = "CollisionCircle2D";
	static constexpr const char* COLLISION_CIRCLE_2D_CENTER_NAME = "center";
	static constexpr const char* COLLISION_CIRCLE_2D_RADIUS_NAME = "radius";

	/**
	* @brief デフォルトコンストラクタ
	*/
	CollisionCircle2D() = default;

	/**
	* @brief コピーコンストラクタ
	* @param[in] base Transformが入った基底クラスポインタ
	*/
	CollisionCircle2D(ComponentDataBase* base)
	{
		CollisionCircle2D* value = dynamic_cast<CollisionCircle2D*>(base);
		center = value->center;
		radius = value->radius;
	}

	/**
	* @brief Jsonデータから値を設定する
	* @param[in] json jsonオブジェクト
	*/
	void SetDataFromJson(nlohmann::json jsonData)override
	{
		center = DirectX::XMFLOAT2(
			jsonData[COLLISION_CIRCLE_2D_CENTER_NAME][0],
			jsonData[COLLISION_CIRCLE_2D_CENTER_NAME][1]
		);
		radius = jsonData[COLLISION_CIRCLE_2D_RADIUS_NAME];
	}

#ifdef _DEBUG
	/**
	* @brief 現在の値をJsonデータに変換する
	*/
	nlohmann::json WriteDataToJson()override
	{
		nlohmann::json jsonData;

		jsonData[COLLISION_CIRCLE_2D_NAME][COLLISION_CIRCLE_2D_CENTER_NAME] = { center.x,center.y };
		jsonData[COLLISION_CIRCLE_2D_NAME][COLLISION_CIRCLE_2D_RADIUS_NAME] = radius;

		return jsonData;
	}

	/**
	* @brief インスペクタ―表示作成
	*/
	GuiItemBase* CreateDetailContent(GuiManager* guiManager)override
	{
		GuiTreeNode* transform_gui = guiManager->CreateGuiTreeNode(COLLISION_CIRCLE_2D_NAME, "id");
		transform_gui->AddChildren(
			guiManager->CreateGuiInputFloat2(COLLISION_CIRCLE_2D_CENTER_NAME, "id", &center, 0.1f),
			guiManager->CreateGuiInputDragFloat(COLLISION_CIRCLE_2D_RADIUS_NAME, "id", &radius, 0.1f,0.1f,2000.0f)
		);
		return transform_gui;
	};
#endif // _DEBUG

	/**
	* @brief ローカル空間での中央位置
	*/
	DirectX::XMFLOAT2 center;

	/**
	* @brief 半径
	*/
	float radius;
};

}// !namespace HaraProject::Framework

#endif // !_COLLISION_CIRCLE_2D_H_