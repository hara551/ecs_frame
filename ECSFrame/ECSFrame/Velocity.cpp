#include "Velocity.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
Velocity::Velocity()
	: linearVelocity(0.0f,0.0f,0.0f)
	, angularVelocity(0.0f,0.0f,0.0f)
{
}

/**
* @brief コピーコンストラクタ
* @param[in] base Velocityが入った基底クラスポインタ
*/
Velocity::Velocity(ComponentDataBase* base)
{
	auto* value = dynamic_cast<Velocity*>(base);
	linearVelocity = value->linearVelocity;
	angularVelocity = value->angularVelocity;
}

/**
* @brief Jsonデータから値を設定する
* @param[in] json jsonオブジェクト
*/
void Velocity::SetDataFromJson(nlohmann::json jsonData)
{
	linearVelocity = DirectX::XMFLOAT3(
		jsonData[VELOCITY_LINEAR_VELOCITY_NAME][0],
		jsonData[VELOCITY_LINEAR_VELOCITY_NAME][1],
		jsonData[VELOCITY_LINEAR_VELOCITY_NAME][2]
	);
	angularVelocity = DirectX::XMFLOAT3(
		jsonData[VELOCITY_ANGULAR_VELOCITY_NAME][0],
		jsonData[VELOCITY_ANGULAR_VELOCITY_NAME][1],
		jsonData[VELOCITY_ANGULAR_VELOCITY_NAME][2]
	);
}

#ifdef _DEBUG
/**
* @brief 現在の値をJsonデータに変換する
*/
nlohmann::json Velocity::WriteDataToJson()
{
	nlohmann::json jsonData;

	jsonData[VELOCITY_NAME][VELOCITY_LINEAR_VELOCITY_NAME] = { linearVelocity.x,linearVelocity.y,linearVelocity.z };
	jsonData[VELOCITY_NAME][VELOCITY_ANGULAR_VELOCITY_NAME] = { angularVelocity.x,angularVelocity.y,angularVelocity.z };

	return jsonData;
}

/**
* @brief インスペクタ―表示作成
*/
GuiItemBase* Velocity::CreateDetailContent(GuiManager* guiManager)
{
	GuiTreeNode* transform_gui = guiManager->CreateGuiTreeNode(VELOCITY_NAME, "id");
	transform_gui->AddChildren(
		guiManager->CreateGuiInputDragFloat3(VELOCITY_LINEAR_VELOCITY_NAME, "id", &linearVelocity, 0.1f),
		guiManager->CreateGuiInputDragFloat3(VELOCITY_ANGULAR_VELOCITY_NAME, "id", &angularVelocity, 0.1f)
	);
	return transform_gui;
};
#endif // _DEBUG

}//!HaraProject::Framework