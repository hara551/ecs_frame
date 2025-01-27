/**
* @file   GuiInputBase.h
* @brief  入力GUI基底クラス.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_INPUT_BASE_H_
#define _GUI_INPUT_BASE_H_

#include <string>
#include <functional>

#include "imgui.h"

#include "GuiItemBase.h"

namespace HaraProject::Framework {

class GuiInputBase : public GuiItemBase
{
public:
	/**
	* @brief 書き換えモード
	*/
	enum OverWriteMode
	{
		Return,
		Always,
	};

	/**
	* @brief コンストラクタ
	* @param[in] title ノードラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] onValueChanged 値変更時に実行する関数
	*/
	GuiInputBase(std::string label, std::string id, OverWriteMode overWriteMode)
		: GuiItemBase(label, id, true), m_on_value_changed(nullptr)
	{
		// 書き換えタイミングのオプションを設定
		switch (overWriteMode)
		{
		case Return: m_over_write_flag = ImGuiInputTextFlags_EnterReturnsTrue; break;
		case Always: m_over_write_flag = ImGuiInputTextFlags_AlwaysOverwrite; break;
		}
	}

	/**
	* @brief 値変更時に実行する関数を設定
	* @param[in] onValueChanged 値変更時に実行する関数
	*/
	void SetOnValueChanged(std::function<void()> onValueChanged) {
		m_on_value_changed = onValueChanged;
	}

protected:
	/**
	* @brief 書き換えタイミングオプションフラグ
	*/
	ImGuiInputTextFlags m_over_write_flag;

	/**
	* @brief 値変更時に実行する関数
	*/
	std::function<void()> m_on_value_changed;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_INPUT_BASE_H_

