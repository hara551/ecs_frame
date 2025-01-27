/**
* @file   GuiButton.h
* @brief  �{�^��GUI.
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
	* @brief �R���X�g���N�^
	* @param[in] label ���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] onSelect �I�����Ɏ��s����֐�
	*/
	GuiButton(std::string label, std::string id, std::function<void()> onClick)
		: GuiItemBase(label, id, true), m_on_click(onClick) {}

	/**
	* @brief �`��
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
	* @brief �������Ɏ��s����֐�
	*/
	std::function<void()> m_on_click;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_BUTTON_H_

