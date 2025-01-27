/**
* @file   GuiButton.h
* @brief  ボタンGUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_BUTTON_H_
#define _GUI_BUTTON_H_

#include <string>
#include <functional>

#include "imgui.h"

#include "GuiItemBase.h"

namespace HaraProject::Framework {

class GuiButton : public GuiItemBase
{
public:
	/**
	* @brief コンストラクタ
	* @param[in] label ラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] onSelect 選択時に実行する関数
	*/
	GuiButton(std::string label, std::string id, std::function<void()> onClick)
		: GuiItemBase(label, id, true), m_on_click(onClick) {}

	/**
	* @brief 描画
	*/
	void Draw()override {
		if (m_is_show)
		{
			if (ImGui::Button(m_imgui_name.c_str()))
			{
				if (m_on_click != nullptr)
				{
					m_on_click();
				}
			}
		}
	}

private:
	/**
	* @brief 押下時に実行する関数
	*/
	std::function<void()> m_on_click;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_BUTTON_H_

