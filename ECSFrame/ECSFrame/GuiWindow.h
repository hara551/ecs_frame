/**
* @file   GuiWindow.h
* @brief  �E�B���h�EGUI.
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
	* @brief �R���X�g���N�^	
	* @param[in] title �E�B���h�E�^�C�g��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] isShow �\���t���O
	* @param[in] pos �\���ʒu 
	* @param[in] size �T�C�Y 
	*/
	GuiWindow(std::string title, std::string id, bool isShow, ImVec2 pos, ImVec2 size)
		: GuiItemBase(title, id, isShow, size), m_position(pos), m_is_open(isShow){}

	/**
	* @brief �`��
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
	* @brief �E�B���h�E�\���ʒu
	*/
	ImVec2 m_position;

	/****/
	bool m_is_open;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_WINDOW_H_

