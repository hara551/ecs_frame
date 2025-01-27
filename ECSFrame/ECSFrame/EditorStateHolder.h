/**
* @file   EditorStateHolder.h
* @brief  エディターの状態を一元管理.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _EDITOR_STATE_HOLDER_H_
#define _EDITOR_STATE_HOLDER_H_

#include <cstdint>
#include <string>

namespace HaraProject::Framework {

class EditorStateHolder
{
public:
	/**
	* @brief 編集モード
	*/
	enum EditMode
	{
		Edit,	// ワールドを編集
		Play	// ワールドを実行
	};

	/**
	* @brief コンストラクタ
	*/
	EditorStateHolder()
		: m_edit_mode(EditMode::Edit)
		, m_select_entity_id(0)
		, m_select_subscene_name("")
		, m_edit_world_name("SubScene_Transform")
	{};

	/**
	* @brief デストラクタ
	*/
	~EditorStateHolder() = default;

	/**
	* @brief 現在の編集モードを取得
	*/
	EditMode GetEditMode() {
		return m_edit_mode;
	}

	/**
	* @brief 選択中のエンティティIDを取得
	*/
	uint32_t GetSelectEntityId() {
		return m_select_entity_id;
	}

	/**
	* @brief 選択中のサブシーン名を取得
	*/
	std::string GetSelectSubSceneName() {
		return m_select_subscene_name;
	}

	/**
	* @brief 編集中のワールド名を取得
	*/
	std::string GetEditWorldName() {
		return m_edit_world_name;
	}

	/**
	* @brief 編集モードを設定
	*/
	void SetEditMode(EditMode editMode) {
		m_edit_mode = editMode;
	}

	/**
	* @brief 選択中のサブシーン名を設定
	* @param[in] subsceneName サブシーン名
	*/
	void SetSelectSubSceneName(std::string subsceneName) {
		m_select_subscene_name = subsceneName;
	}

	/**
	* @brief 選択中のエンティティIDを設定
	* @param[in] id エンティティID
	*/
	void SetSelectEntityId(uint32_t id) {
		m_select_entity_id = id;
	}

	/**
	* @brief 編集中のワールド名を設定
	* @param[in] worldName ワールド名
	*/
	void SetEditWorldName(std::string worldName) {
		m_edit_world_name = worldName;
	}

private:
	/**
	* @brief 現在の編集モード
	*/
	EditMode m_edit_mode;

	/**
	* @brief 選択中のエンティティID
	*/
	uint32_t m_select_entity_id;

	/**
	* @brief 選択中のサブシーン名
	*/
	std::string m_select_subscene_name;

	/**
	* @brief 編集中のワールド名
	*/
	std::string m_edit_world_name;
};

}// !namespace HaraProject::Framework

#endif // !_EDITOR_STATE_HOLDER_H_
