/**
* @file   GuiSelectable.h
* @brief  �I������GUI.
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
	* @brief �R���X�g���N�^
	* @param[in] label ���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] onSelect �I�����Ɏ��s����֐�
	*/
	GuiSelectable(std::string label, std::string id, std::function<void()> onSelect)
		: GuiItemBase(label, id, true), m_on_select(onSelect) {}

	/**
	* @brief �`��
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
	* @brief �I�����Ɏ��s����֐�
	*/
	std::function<void()> m_on_select;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_SELECTABLE_H_

