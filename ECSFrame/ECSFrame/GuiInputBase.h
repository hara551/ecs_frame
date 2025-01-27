/**
* @file   GuiInputBase.h
* @brief  ����GUI���N���X.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_INPUT_BASE_H_
#define _GUI_INPUT_BASE_H_

#include <string>
#include <functional>

#include "imgui.h"

#include "GuiItemBase.h"

namespace HaraProject::Framework {

class GuiInputBase : public GuiItemBase
{
public:
	/**
	* @brief �����������[�h
	*/
	enum OverWriteMode
	{
		Return,
		Always,
	};

	/**
	* @brief �R���X�g���N�^
	* @param[in] title �m�[�h���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] onValueChanged �l�ύX���Ɏ��s����֐�
	*/
	GuiInputBase(std::string label, std::string id, OverWriteMode overWriteMode)
		: GuiItemBase(label, id, true), m_on_value_changed(nullptr)
	{
		// ���������^�C�~���O�̃I�v�V������ݒ�
		switch (overWriteMode)
		{
		case Return: m_over_write_flag = ImGuiInputTextFlags_EnterReturnsTrue; break;
		case Always: m_over_write_flag = ImGuiInputTextFlags_AlwaysOverwrite; break;
		}
	}

	/**
	* @brief �l�ύX���Ɏ��s����֐���ݒ�
	* @param[in] onValueChanged �l�ύX���Ɏ��s����֐�
	*/
	void SetOnValueChanged(std::function<void()> onValueChanged) {
		m_on_value_changed = onValueChanged;
	}

protected:
	/**
	* @brief ���������^�C�~���O�I�v�V�����t���O
	*/
	ImGuiInputTextFlags m_over_write_flag;

	/**
	* @brief �l�ύX���Ɏ��s����֐�
	*/
	std::function<void()> m_on_value_changed;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_INPUT_BASE_H_

