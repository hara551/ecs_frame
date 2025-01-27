/**
* @file   Velocity.h
* @brief  速度コンポーネントデータ定義.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _VELOCITY_H_
#define _VELOCITY_H_

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

namespace HaraProject::Framework{
/**
* @brief 速度コンポーネントデータ
*/
class Velocity : public ComponentDataBase
{
public:
	/**
	* @brief データ名
	*/
	static constexpr const char* VELOCITY_NAME = "Velocity";
	static constexpr const char* VELOCITY_LINEAR_VELOCITY_NAME = "linearVelocity";
	static constexpr const char* VELOCITY_ANGULAR_VELOCITY_NAME = "angularVelocity";

	/**
	* @brief 移動速度
	*/
	DirectX::XMFLOAT3 linearVelocity;

	/**
	* @brief 回転速度
	*/
	DirectX::XMFLOAT3 angularVelocity;

	/**
	* @brief コンストラクタ
	*/
	Velocity();

	/**
	* @brief コピーコンストラクタ
	* @param[in] base コピー元のVelocity
	*/
	Velocity(ComponentDataBase* base);

	/**
	* @brief デストラクタ
	*/
	~Velocity() = default;

	/**
	* @brief Jsonデータから値を設定する
	* @param[in] json jsonオブジェクト
	*/
	void SetDataFromJson(nlohmann::json jsonData)override;

#ifdef _DEBUG
	/**
	* @brief 現在の値をJsonデータに変換する
	*/
	nlohmann::json WriteDataToJson()override;

	/**
	* @brief インスペクタ―表示作成
	*/
	GuiItemBase* CreateDetailContent(GuiManager* guiManager)override;
#endif // _DEBUG
};

}// !namespace HaraProject::Framework

#endif // !_VELOCITY_H_