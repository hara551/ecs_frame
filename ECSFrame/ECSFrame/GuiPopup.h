/**
* @file   GuiPopup.h
* @brief  �|�b�v�A�b�vGUI.
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
	* @brief �R���X�g���N�^
	* @param[in] title �|�b�v�A�b�v�^�C�g��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] isShow �\���t���O
	*/
	GuiPopup(std::string title, std::string id, bool isShow = false)
		: GuiItemBase(title, id, isShow){}

	/**
	* @brief �`��
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
				// �Ō���ɕ���{�^����ǉ�
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
	* @brief �|�b�v�A�b�v�����
	*/
	void ClosePopup() {
		ImGui::CloseCurrentPopup();
		SetShow(false);
	}
};

}// !namespace HaraProject::Framework

#endif // !_GUI_POPUP_H_

