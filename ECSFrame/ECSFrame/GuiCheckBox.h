/**
* @file   GuiCheckBox.h
* @brief  �`�F�b�N�{�b�N�XGUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_CHECK_BOX_H_
#define _GUI_CHECK_BOX_H_

#include <string>
#include <functional>

#include "imgui.h"

#include "GuiInputBase.h"

namespace HaraProject::Framework {

class GuiCheckBox : public GuiInputBase
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param[in] title �m�[�h���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] outputBuffer �l�ύX���ɒl���i�[����o�b�t�@
	* @param[in] onChage �`�F�b�N��ԕύX���Ɏ��s����֐�
	*/
	GuiCheckBox(std::string label, std::string id, bool* outputBuffer, std::function<void()> onChange = nullptr)
		: GuiInputBase(label, id, GuiInputBase::Always), m_output_buffer(outputBuffer), m_on_change_check(onChange){}

	/**
	* @brief �`��
	*/
	void Draw()override {
		if (m_is_show)
		{
			if (ImGui::Checkbox(m_imgui_name.c_str(), m_output_buffer))
			{
				if (m_on_change_check != nullptr)
				{
					m_on_change_check();
				}
			}
		}
	}

private:
	/**
	* @brief �o�͗p�o�b�t�@
	*/
	bool* m_output_buffer;

	/**
	* @brief �`�F�b�N��ԕύX���Ɏ��s����֐�
	*/
	std::function<void()> m_on_change_check;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_CHECK_BOX_H_

