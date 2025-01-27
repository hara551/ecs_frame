/**
* @file   GuiTreeNode.h
* @brief  �K�w�\��GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_TREE_NODE_H_
#define _GUI_TREE_NODE_H_

#include <string>
#include <functional>

#include "imgui.h"

#include "GuiItemBase.h"

namespace HaraProject::Framework {

class GuiTreeNode : public GuiItemBase
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param[in] title �m�[�h���x��
	* @param[in] id ����ID�d���h�~�p�̔C�ӂ̎��ʎq
	* @param[in] isDefaultOpen �����m�[�h�J�t���O
	* @param[in] onSelect �I�����Ɏ��s����֐�
	*/
	GuiTreeNode(std::string label, std::string id, bool isDefaultOpen = true,
		std::function<void()> onSelect = nullptr, std::function<void()> onClickRight = nullptr, bool isLeaf = false)
		: GuiItemBase(label, id, true), m_on_select(onSelect), m_on_click_right(onClickRight)
	{
		m_node_open_flag = isDefaultOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None;
		if (isLeaf)
		{
			m_node_open_flag = m_node_open_flag | ImGuiTreeNodeFlags_Leaf;
		}
	}

	/**
	* @brief �`��
	*/
	void Draw()override {
		if (m_is_show)
		{
			if (ImGui::TreeNodeEx(m_imgui_name.c_str(), m_node_open_flag))
			{
				if (ImGui::IsItemClicked())
				{
					if(m_on_select != nullptr)
						m_on_select();
				}
				if (ImGui::IsItemClicked(ImGuiMouseButton_::ImGuiMouseButton_Right))
				{
					if (m_on_click_right != nullptr)
						m_on_click_right();
				}

				for (const auto& child : m_children)
				{
					child->Draw();
				}
				ImGui::TreePop();
			}
		}
	}
	
private:
	/**
	* @brief �I�����Ɏ��s����֐�
	*/
	std::function<void()> m_on_select;

	/**
	* @brief �E�N���b�N���Ɏ��s����֐�
	*/
	std::function<void()> m_on_click_right;

	/**
	* @brief �m�[�h�J�I�v�V�����t���O
	*/
	ImGuiTreeNodeFlags m_node_open_flag;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_TREE_NODE_H_

