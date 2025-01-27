/**
* @file   GuiInputColor.h
* @brief  Color����GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_INPUT_COLOR_H_
#define _GUI_INPUT_COLOR_H_

#include <DirectXMath.h>

#include <cstdint>
#include <string>

#include "imgui.h"

#include "GuiInputBase.h"

namespace HaraProject::Framework {

class GuiInputColor : public GuiInputBase
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param[in] label ���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] outputBuffer �l�ύX���ɒl���i�[����o�b�t�@
	*/
	GuiInputColor(std::string label, std::string id, DirectX::XMFLOAT4* outputBuffer)
		: GuiInputBase(label, id, Always), m_output_buffer(outputBuffer)
	{
		m_input_buffer[0] = outputBuffer->x;
		m_input_buffer[1] = outputBuffer->y;
		m_input_buffer[2] = outputBuffer->z;
		m_input_buffer[3] = outputBuffer->w;
	}

	/**
	* @brief �`��
	*/
	void Draw()override {
		if (m_is_show)
		{
			if(ImGui::ColorEdit4(m_label.c_str(), m_input_buffer))
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
			m_input_buffer[2],
			m_input_buffer[3]
		};
	}

	/**
	* @brief ���͗p�o�b�t�@
	*/
	float m_input_buffer[4];

	/**
	* @brief �o�͗p�o�b�t�@
	*/
	DirectX::XMFLOAT4* m_output_buffer;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_INPUT_COLOR_H_

