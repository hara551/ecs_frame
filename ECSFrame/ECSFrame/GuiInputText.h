/**
* @file   GuiInputText.h
* @brief  �e�L�X�g����GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_INPUT_TEXT_H_
#define _GUI_INPUT_TEXT_H_

#include <string.h>

#include <cstdint>
#include <string>

#include "imgui.h"

#include "GuiInputBase.h"

namespace HaraProject::Framework {

class GuiInputText : public GuiInputBase
{
public:
	/**
	* @brief �ő���͕�����
	*/
	static constexpr uint8_t MAX_INPUT_TEXT_LENGTH = 50;

	/**
	* @brief �R���X�g���N�^
	* @param[in] title �m�[�h���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] overWriteMode ���������^�C�~���O�I�v�V����
	* @param[in] outputBuffer �l�ύX���ɒl���i�[����o�b�t�@
	*/
	GuiInputText(std::string label, std::string id, OverWriteMode overWriteMode, char* outputBuffer)
		: GuiInputBase(label, id, overWriteMode), m_output_buffer(outputBuffer)
	{
		strcpy_s(m_input_buffer, MAX_INPUT_TEXT_LENGTH, m_output_buffer);
	}

	/**
	* @brief �`��
	*/
	void Draw()override{
		if (m_is_show)
		{
			if (ImGui::InputText(m_imgui_name.c_str(), m_input_buffer, MAX_INPUT_TEXT_LENGTH, m_over_write_flag))
			{
				ChangeValue(m_output_buffer);
			}
		}
	}

private:
	/**
	* @brief �����̃o�b�t�@�ɒl��ݒ�
	* @param[in] charBuffer �l���i�[����o�b�t�@
	*/
	void ChangeValue(char* charBuffer) {
		strcpy_s(charBuffer, MAX_INPUT_TEXT_LENGTH, m_input_buffer);
	}

	/**
	* @brief ���͗p�o�b�t�@
	*/
	char m_input_buffer[MAX_INPUT_TEXT_LENGTH];

	/**
	* @brief �o�͗p�o�b�t�@
	*/
	char* m_output_buffer;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_INPUT_TEXT_H_

