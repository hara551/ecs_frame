/**
* @file   GuiWindow.h
* @brief  ウィンドウGUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_WINDOW_H_
#define _GUI_WINDOW_H_

#include <string>

#include "imgui.h"

#include "GuiItemBase.h"

namespace HaraProject::Framework {

class GuiWindow : public GuiItemBase
{
public:
	/**
	* @brief コンストラクタ	
	* @param[in] title ウィンドウタイトル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] isShow 表示フラグ
	* @param[in] pos 表示位置 
	* @param[in] size サイズ 
	*/
	GuiWindow(std::string title, std::string id, bool isShow, ImVec2 pos, ImVec2 size)
		: GuiItemBase(title, id, isShow, size), m_position(pos), m_is_open(isShow){}

	/**
	* @brief 描画
	*/
	void Draw()override{
		if (m_is_show)
		{
			ImGuiWindowFlags flag = ImGuiWindowFlags_NoCollapse/* | ImGuiWindowFlags_MenuBar*/;
			if (ImGui::Begin(m_imgui_name.c_str(),&m_is_open, flag))
			{
	//			ImGui::SetWindowSize(m_size);
	//			ImGui::SetWindowPos(m_position);
				for (const auto& child : m_children)
				{
					child->Draw();
				}
				ImGui::End();
			}
		}
	}

private:
	/**
	* @brief ウィンドウ表示位置
	*/
	ImVec2 m_position;

	/****/
	bool m_is_open;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_WINDOW_H_

