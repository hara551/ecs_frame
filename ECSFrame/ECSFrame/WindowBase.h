/**
* @file   WindowBase.h
* @brief  ウィンドウ基底クラス.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _WINDOW_BASE_H_
#define _WINDOW_BASE_H_

#include "GuiWindow.h"

namespace HaraProject::Framework {

class EditorManager;

class WindowBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	WindowBase(EditorManager* editorManager);
		
	/**
	* @brief デストラクタ
	*/
	virtual ~WindowBase() = default;

	/**
	* @brief 更新処理
	*/
	virtual void UpdateWindow() { m_need_update = false; };

	/**
	* @brief 更新が必要か
	*/
	bool NeedUpdate() { return m_need_update; }

	/**
	* @brief 更新フラグを設定
	* @param[in] needUpdate 更新フラグ
	*/
	void SetNeedUpdate(bool needUpdate) { m_need_update = needUpdate; }

	/**
	* @brief ウィンドウ削除
	*/
	void DeleteWindow();

	/**
	* @brief ウィンドウ表示設定
	*/
	void SetShow(bool isShow) { m_window->SetShow(isShow); }

	/**
	* @brief 削除するか
	*/
	bool IsDlelete() { return m_is_delete; }

	/**
	* @brief 削除フラグ設定
	* @param[in] isDelete 削除フラグ
	*/
	void SetIsDelete(bool isDelete) { m_is_delete = isDelete; }

protected:
	/**
	* @brief エディター全体管理
	*/
	EditorManager* m_editor_manager;

	/**
	* @brief ウィンドウアイテム
	*/
	GuiWindow* m_window;

	/**
	* @brief 更新フラグ
	*/
	bool m_need_update;

	/**
	* @brief 削除フラグ
	*/
	bool m_is_delete;
};

}// !namespace HaraProject::Framework {


#endif // !_WINDOW_BASE_H_
