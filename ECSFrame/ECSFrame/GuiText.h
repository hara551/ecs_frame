/**
* @file   GuiText.h
* @brief  �e�L�X�g�o��GUI.
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
	* @brief �R���X�g���N�^
	* @param[in] text �e�L�X�g
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	*/
	GuiText(std::string text)
		: GuiItemBase(text, "") {}

	/**
	* @brief �`��
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

