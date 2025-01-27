/**
* @file   GuiInputFloat.h
* @brief  Float����GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_INPUT_FLOAT_H_
#define _GUI_INPUT_FLOAT_H_

#include <cstdint>
#include <string>

#include "imgui.h"

#include "GuiInputBase.h"

namespace HaraProject::Framework {

class GuiInputFloat : public GuiInputBase
{
public:
	/**
	* @brief ����̕\�����鏭������
	*/
	static constexpr uint8_t DEFAULT_DECIMAL_PLACES = 2;

	/**
	* @brief �{�[�{�^���ő������鐔
	*/
	static constexpr float DEFAULT_FLOAT_STEP = 0.1f;

	/**
	* @brief Ctr & �{�[�{�^���ő������鐔
	*/
	static constexpr float DEFAULT_FAST_FLOAT_STEP = 10.0f;

	/**
	* @brief �R���X�g���N�^
	* @param[in] title �m�[�h���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] outputBuffer �l�ύX���ɒl���i�[����o�b�t�@
	* @param[in] decimalPlaces �\�����鏭������
	* @param[in] overWriteMode ���������^�C�~���O�I�v�V����
	*/
	GuiInputFloat(std::string label, std::string id, float* outputBuffer,
				  int decimalPlaces = DEFAULT_DECIMAL_PLACES, OverWriteMode overWriteMode = GuiInputBase::Always)
		: GuiInputBase(label, id, overWriteMode), m_output_buffer(outputBuffer)
	{
		std::string str = std::to_string(decimalPlaces);
		str = "%." + str + "f";
		m_decimal_places = str;
	}

	/**
	* @brief �`��
	*/
	void Draw()override {
		if (m_is_show)
		{
			ImGui::InputFloat(m_imgui_name.c_str(), m_output_buffer, DEFAULT_FLOAT_STEP,
				DEFAULT_FAST_FLOAT_STEP,m_decimal_places.c_str(), m_over_write_flag);
		}
	}

private:
	/**
	* @brief �o�͗p�o�b�t�@
	*/
	float* m_output_buffer;

	/**
	* @brief �\�����鏭������
	*/
	std::string m_decimal_places;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_INPUT_FLOAT_H_

