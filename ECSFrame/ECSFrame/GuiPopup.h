/**
* @file   GuiPopup.h
* @brief  ポップアップGUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_POPUP_H_
#define _GUI_POPUP_H_

#include <string>

#include "imgui.h"

#include "GuiItemBase.h"

namespace HaraProject::Framework {

class GuiPopup : public GuiItemBase
{
public:
	/**
	* @brief コンストラクタ
	* @param[in] title ポップアップタイトル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] isShow 表示フラグ
	*/
	GuiPopup(std::string title, std::string id, bool isShow = false)
		: GuiItemBase(title, id, isShow){}

	/**
	* @brief 描画
	*/
	void Draw()override {
		if (m_is_show)
		{
			if (ImGui::BeginPopup(m_imgui_name.c_str()))
			{
				for (const auto& child : m_children)
				{
					child->Draw();
				}
				// 最後尾に閉じるボタンを追加
				if (ImGui::Selectable("Close"))
				{
					ClosePopup();
				}
				ImGui::EndPopup();
			}
			ImGui::OpenPopup(m_imgui_name.c_str());
		}
	}

	/**
	* @brief ポップアップを閉じる
	*/
	void ClosePopup() {
		ImGui::CloseCurrentPopup();
		SetShow(false);
	}
};

}// !namespace HaraProject::Framework

#endif // !_GUI_POPUP_H_

