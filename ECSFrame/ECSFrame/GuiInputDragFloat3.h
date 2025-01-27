/**
* @file   GuiInputDragFloat.h
* @brief  �}�E�X�h���b�OFloat����GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_INPUT_DRAG_FLOAT3_H_
#define _GUI_INPUT_DRAG_FLOAT3_H_

#include <DirectXMath.h>

#include <cstdint>
#include <string>

#include "imgui.h"

#include "GuiInputBase.h"

namespace HaraProject::Framework {

class GuiInputDragFloat3 : public GuiInputBase
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
	GuiInputDragFloat3(std::string label, std::string id,DirectX::XMFLOAT3* outputBuffer, float dragSpeed)
		: GuiInputBase(label, id, OverWriteMode::Always), m_output_buffer(outputBuffer), m_drag_speed(dragSpeed)
	{
		m_input_buffer[0] = outputBuffer->x;
		m_input_buffer[1] = outputBuffer->y;
		m_input_buffer[2] = outputBuffer->z;
	}

	/**
	* @brief �`��
	*/
	void Draw()override {
		if (m_is_show)
		{
			if (ImGui::DragFloat3(m_imgui_name.c_str(), m_input_buffer, m_drag_speed))
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
			m_input_buffer[2]
		};
	}
	/**
	* @brief ���͗p�o�b�t�@
	*/
	float m_input_buffer[3];

	/**
	* @brief �o�͗p�o�b�t�@
	*/
	DirectX::XMFLOAT3* m_output_buffer;

	/**
	* @brief �h���b�O�ŕς��l�̑���
	*/
	float m_drag_speed;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_INPUT_DRAG_FLOAT3_H_

