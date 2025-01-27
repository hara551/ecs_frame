/**
* @file   GuiInputFloat2.h
* @brief  Float2����GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_INPUT_FLOAT2_H_
#define _GUI_INPUT_FLOAT2_H_

#include <DirectXMath.h>

#include <cstdint>
#include <string>

#include "imgui.h"

#include "GuiInputBase.h"
#include "GuiInputFloat.h"

namespace HaraProject::Framework {

class GuiInputFloat2 : public GuiInputBase
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param[in] title �m�[�h���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] outputBuffer �l�ύX���ɒl���i�[����o�b�t�@
	* @param[in] decimalPlaces �\�����鏭������
	* @param[in] overWriteMode ���������^�C�~���O�I�v�V����
	*/
	GuiInputFloat2(std::string label, std::string id, DirectX::XMFLOAT2* outputBuffer,
		int decimalPlaces = GuiInputFloat::DEFAULT_DECIMAL_PLACES, OverWriteMode overWriteMode = GuiInputBase::Always)
		: GuiInputBase(label, id, overWriteMode), m_output_buffer(outputBuffer)
	{
		std::string str = std::to_string(decimalPlaces);
		str = "%." + str + "f";
		m_decimal_places = str;

		m_input_buffer[0] = outputBuffer->x;
		m_input_buffer[1] = outputBuffer->y;
	}

	/**
	* @brief �`��
	*/
	void Draw()override {
		if (m_is_show)
		{
			if (ImGui::InputFloat2(m_imgui_name.c_str(), m_input_buffer, m_decimal_places.c_str(), m_over_write_flag))
			{
				ChangeValue();
			}
		}
	}

private:
	/**
	* @brief �o�͗p�o�b�t�@�ɒl���i�[
	*/
	void ChangeValue() {
		*m_output_buffer = {
			m_input_buffer[0],
			m_input_buffer[1],
		};
	}

	/**
	* @brief ���͗p�o�b�t�@
	*/
	float m_input_buffer[2];

	/**
	* @brief �o�͗p�o�b�t�@
	*/
	DirectX::XMFLOAT2* m_output_buffer;

	/**
	* @brief �\�����鏭������
	*/
	std::string m_decimal_places;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_INPUT_FLOAT3_H_

