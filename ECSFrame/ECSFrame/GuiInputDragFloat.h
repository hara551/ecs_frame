/**
* @file   GuiInputDragFloat.h
* @brief  �}�E�X�h���b�OFloat����GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_INPUT_DRAG_FLOAT_H_
#define _GUI_INPUT_DRAG_FLOAT_H_

#include <cstdint>
#include <string>

#include "imgui.h"

#include "GuiInputBase.h"

namespace HaraProject::Framework {

class GuiInputDragFloat : public GuiInputBase
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
	GuiInputDragFloat(std::string label, std::string id, float* outputBuffer, float dragSpeed , float min, float max)
		: GuiInputBase(label, id, OverWriteMode::Always), m_output_buffer(outputBuffer), m_drag_speed(dragSpeed)
		, m_min(min), m_max(max)
	{
	}

	/**
	* @brief �`��
	*/
	void Draw()override {
		if (m_is_show)
		{
			ImGui::DragFloat(m_imgui_name.c_str(), m_output_buffer, m_drag_speed, m_min, m_max);
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

	/**
	* @brief �h���b�O�ŕς��l�̑���
	*/
	float m_drag_speed;

	/**
	* @brief �ŏ��l
	*/
	float m_min;

	/**
	* @brief �ő�l
	*/
	float m_max;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_INPUT_DRAG_FLOAT_H_

