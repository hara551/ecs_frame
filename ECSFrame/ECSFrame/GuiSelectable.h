/**
* @file   GuiSelectable.h
* @brief  選択項目GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_SELECTABLE_H_
#define _GUI_SELECTABLE_H_

#include <string>
#include <functional>

#include "imgui.h"

#include "GuiItemBase.h"

namespace HaraProject::Framework {

class GuiSelectable : public GuiItemBase
{
public:
	/**
	* @brief コンストラクタ
	* @param[in] label ラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] onSelect 選択時に実行する関数
	*/
	GuiSelectable(std::string label, std::string id, std::function<void()> onSelect)
		: GuiItemBase(label, id, true), m_on_select(onSelect) {}

	/**
	* @brief 描画
	*/
	void Draw()override {
		if (m_is_show)
		{
			if (ImGui::Selectable(m_imgui_name.c_str()))
			{
				m_on_select();
			}
		}
	}

private:
	/**
	* @brief 選択時に実行する関数
	*/
	std::function<void()> m_on_select;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_SELECTABLE_H_

