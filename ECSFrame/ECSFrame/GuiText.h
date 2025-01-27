/**
* @file   GuiText.h
* @brief  テキスト出力GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_TEXT_H_
#define _GUI_TEXT_H_

#include <string>

#include "imgui.h"

#include "GuiItemBase.h"

namespace HaraProject::Framework {

class GuiText : public GuiItemBase
{
public:
	/**
	* @brief コンストラクタ
	* @param[in] text テキスト
	* @param[in] id 内部ID重複防止用の任意の識別子
	*/
	GuiText(std::string text)
		: GuiItemBase(text, "") {}

	/**
	* @brief 描画
	*/
	void Draw()override {
		if (m_is_show)
		{
			ImGui::Text(m_label.c_str());
		}
	}
};

}// !namespace HaraProject::Framework

#endif // !_GUI_TEXT_H_

