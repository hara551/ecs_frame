/**
* @file   GuiInputInt.h
* @brief  Int����GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_INPUT_INT_H_
#define _GUI_INPUT_INT_H_

#include <string>

#include "imgui.h"

#include "GuiInputBase.h"

namespace HaraProject::Framework {

class GuiInputInt : public GuiInputBase
{
public:
	/**
	* @brief �{�[�{�^���ő������鐔
	*/
	static constexpr int DEFAULT_INT_STEP = 1;

	/**
	* @brief Ctr & �{�[�{�^���ő������鐔
	*/
	static constexpr int DEFAULT_FAST_INT_STEP = 100;

	/**
	* @brief �R���X�g���N�^
	* @param[in] title �m�[�h���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] outputBuffer �l�ύX���ɒl���i�[����o�b�t�@
	* @param[in] overWriteMode ���������^�C�~���O�I�v�V����
	*/
	GuiInputInt(std::string label, std::string id, int* outputBuffer, OverWriteMode overWriteMode = GuiInputBase::Always)
		: GuiInputBase(label, id, overWriteMode), m_output_buffer(outputBuffer){}

	/**
	* @brief �`��
	*/
	void Draw()override {
		if (m_is_show)
		{
			ImGui::InputInt(m_imgui_name.c_str(), m_output_buffer,
				DEFAULT_INT_STEP, DEFAULT_FAST_INT_STEP, m_over_write_flag);
		}
	}

private:
	/**
	* @brief �o�͗p�o�b�t�@
	*/
	int* m_output_buffer;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_INPUT_INT_H_

