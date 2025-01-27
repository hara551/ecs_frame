/**
* @file   GuiItemBase.h
* @brief  GUIアイテム基底クラス.
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
	* @brief コンストラクタ
	* @param[in] label ラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] 表示フラグ
	*/
	GuiItemBase(std::string label, std::string id, bool isShow = true)
		: m_label(label), m_id(id), m_imgui_name(m_label + "##" + m_id)
		, m_is_show(isShow), m_size(ImVec2(-100, -100)), m_cursor_offset(ImVec2(-100, -100)), m_color(ImVec4(-1, -1, -1, -1)) {}

	/**
	* @brief コンストラクタ
	* @param[in] label ラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] isShow 表示フラグ
	* @param[in] size サイズ
	* @param[in] color 色
	*/
	GuiItemBase(std::string label, std::string id, bool isShow, ImVec2 size)
		: m_label(label), m_id(id), m_imgui_name(m_label + "##" + m_id)
		, m_is_show(isShow), m_size(size), m_cursor_offset(ImVec2(-100, -100)), m_color(ImVec4(-1, -1, -1, -1))
		, m_parent(nullptr){}

	/**
	* @brief デストラクタ
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
	* @brief 描画
	*/
	virtual void Draw() = 0;

	/**
	* @brief 親を設定
	*/
	void SetParent(GuiItemBase* parent) {
		m_parent = parent;
	}

	/**
	* @brief 子アイテム追加
	* @param[in] item 子アイテム
	*/
	void AddChild(GuiItemBase* item) {
		item->SetParent(this);
		m_children.push_back(item);
	}

	/**
	* @brief 複数子アイテム追加
	* @param[in] items 子アイテム
	*/
	template<typename ... GuiItem>
	void AddChildren(GuiItem...items){
		(AddChild(items), ...);
	}

	/**
	* @brief 子アイテム取得
	* @param label アイテム名
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
	* @brief 全子アイテム取得
	*/
	std::vector<GuiItemBase*> GetChildren() {
		return m_children;
	}

	/**
	* @brief 子アイテムを持っているか
	*/
	bool HasChild() {
		return m_children.size() != 0;
	}

	/**
	* @brief 表示非表示設定
	* @param[in] isShow 表示フラグ
	*/
	void SetShow(bool isShow) {
		m_is_show = isShow;
	}

	/**
	* @brief 表示するか
	*/
	bool IsShow() {
		return m_is_show;
	}

	/**
	* @brief ラベル取得
	*/
	std::string GetLabel() {
		return m_label;
	}

	/**
	* @brief 親の子から自分を削除する
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
	* @brief 親アイテム
	*/
	GuiItemBase* m_parent;

	/**
	* @brief 子アイテム
	*/
	std::vector<GuiItemBase*> m_children;

	/**
	* @brief ラベル
	*/
	std::string m_label;

	/**
	* @brief ID
	*/
	std::string m_id;

	/**
	* @brief ImGuiに渡す名前
	*/
	std::string m_imgui_name;

	/**
	* @brief サイズ
	*/
	ImVec2 m_size;

	/**
	* @brief 直前描画位置からのオフセット
	*/
	ImVec2 m_cursor_offset;

	/**
	* @brief 色
	*/
	ImVec4 m_color;

	/**
	* @brief 表示フラグ
	*/
	bool m_is_show;
};

}// !namespace HaraProject::Framework


#endif // !_GUI_ITEM_BASE_H_