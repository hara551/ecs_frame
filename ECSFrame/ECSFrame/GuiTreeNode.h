/**
* @file   GuiTreeNode.h
* @brief  階層構造GUI.
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
	* @brief コンストラクタ
	* @param[in] title ノードラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] isDefaultOpen 初期ノード開閉フラグ
	* @param[in] onSelect 選択時に実行する関数
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
	* @brief 描画
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
	* @brief 選択時に実行する関数
	*/
	std::function<void()> m_on_select;

	/**
	* @brief 右クリック時に実行する関数
	*/
	std::function<void()> m_on_click_right;

	/**
	* @brief ノード開閉オプションフラグ
	*/
	ImGuiTreeNodeFlags m_node_open_flag;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_TREE_NODE_H_

