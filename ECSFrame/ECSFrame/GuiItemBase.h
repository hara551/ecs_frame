/**
* @file   GuiItemBase.h
* @brief  GUI�A�C�e�����N���X.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_ITEM_BASE_H_
#define _GUI_ITEM_BASE_H_

#include <string>
#include <vector>

#include "imgui.h"

namespace HaraProject::Framework {

class GuiItemBase
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param[in] label ���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] �\���t���O
	*/
	GuiItemBase(std::string label, std::string id, bool isShow = true)
		: m_label(label), m_id(id), m_imgui_name(m_label + "##" + m_id)
		, m_is_show(isShow), m_size(ImVec2(-100, -100)), m_cursor_offset(ImVec2(-100, -100)), m_color(ImVec4(-1, -1, -1, -1)) {}

	/**
	* @brief �R���X�g���N�^
	* @param[in] label ���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] isShow �\���t���O
	* @param[in] size �T�C�Y
	* @param[in] color �F
	*/
	GuiItemBase(std::string label, std::string id, bool isShow, ImVec2 size)
		: m_label(label), m_id(id), m_imgui_name(m_label + "##" + m_id)
		, m_is_show(isShow), m_size(size), m_cursor_offset(ImVec2(-100, -100)), m_color(ImVec4(-1, -1, -1, -1))
		, m_parent(nullptr){}

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~GuiItemBase() 
	{
		for (auto& child : m_children) 
		{
			if (child != nullptr) 
			{
				delete child;
				child = nullptr;
			}
		}
	}

	/**
	* @brief �`��
	*/
	virtual void Draw() = 0;

	/**
	* @brief �e��ݒ�
	*/
	void SetParent(GuiItemBase* parent) {
		m_parent = parent;
	}

	/**
	* @brief �q�A�C�e���ǉ�
	* @param[in] item �q�A�C�e��
	*/
	void AddChild(GuiItemBase* item) {
		item->SetParent(this);
		m_children.push_back(item);
	}

	/**
	* @brief �����q�A�C�e���ǉ�
	* @param[in] items �q�A�C�e��
	*/
	template<typename ... GuiItem>
	void AddChildren(GuiItem...items){
		(AddChild(items), ...);
	}

	/**
	* @brief �q�A�C�e���擾
	* @param label �A�C�e����
	*/
	GuiItemBase* GetChild(std::string label) 
	{
		for (const auto& child : m_children) 
		{
			if (child->GetLabel() == label)
				return child;
		}
		return nullptr;
	}

	/**
	* @brief �S�q�A�C�e���擾
	*/
	std::vector<GuiItemBase*> GetChildren() {
		return m_children;
	}

	/**
	* @brief �q�A�C�e���������Ă��邩
	*/
	bool HasChild() {
		return m_children.size() != 0;
	}

	/**
	* @brief �\����\���ݒ�
	* @param[in] isShow �\���t���O
	*/
	void SetShow(bool isShow) {
		m_is_show = isShow;
	}

	/**
	* @brief �\�����邩
	*/
	bool IsShow() {
		return m_is_show;
	}

	/**
	* @brief ���x���擾
	*/
	std::string GetLabel() {
		return m_label;
	}

	/**
	* @brief �e�̎q���玩�����폜����
	*/
	void DetachParent() 
	{
		if (m_parent != nullptr)
		{
			std::vector<GuiItemBase*> brother = m_parent->GetChildren();
			std::erase_if(brother,
				[&](GuiItemBase* item)
				{
					return item->GetLabel() == m_label;
				});
		}
	}

protected:
	/**
	* @brief �e�A�C�e��
	*/
	GuiItemBase* m_parent;

	/**
	* @brief �q�A�C�e��
	*/
	std::vector<GuiItemBase*> m_children;

	/**
	* @brief ���x��
	*/
	std::string m_label;

	/**
	* @brief ID
	*/
	std::string m_id;

	/**
	* @brief ImGui�ɓn�����O
	*/
	std::string m_imgui_name;

	/**
	* @brief �T�C�Y
	*/
	ImVec2 m_size;

	/**
	* @brief ���O�`��ʒu����̃I�t�Z�b�g
	*/
	ImVec2 m_cursor_offset;

	/**
	* @brief �F
	*/
	ImVec4 m_color;

	/**
	* @brief �\���t���O
	*/
	bool m_is_show;
};

}// !namespace HaraProject::Framework


#endif // !_GUI_ITEM_BASE_H_