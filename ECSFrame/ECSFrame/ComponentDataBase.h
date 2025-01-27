/**
* @file   ComponentDataBase.h
* @brief  コンポーネントデータ基底クラス定義.
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
* @brief コンポーネントデータ基底
*/
class ComponentDataBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	ComponentDataBase() = default;

	/**
	* @brief デストラクタ
	*/
	virtual ~ComponentDataBase() = default;

	/**
	* @brief データ無効化
	*/
	void Disable() { isAble = false; }

	/**
	* @brief データが有効か
	*/
	bool IsAble() { return isAble; }

	/**
	* @brief Jsonデータから値を設定する
	* @param[in] json jsonオブジェクト
	*/
	virtual void SetDataFromJson(nlohmann::json json) = 0;

#ifdef _DEBUG
	/**
	* @brief 現在の値をJsonデータに変換する
	*/
	virtual nlohmann::json WriteDataToJson() { return nlohmann::json(); };

	/**
	* @brief インスペクタ―表示作成
	*/
	virtual GuiItemBase* CreateDetailContent(GuiManager* guiManager) { return nullptr; }
#endif // _DEBUG

protected:
	/**
	* @brief データ有効フラグ
	*/
	bool isAble = true;;
};

}

#endif // !_COMPONENT_DATA_BASE_H_
