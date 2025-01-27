#ifdef _DEBUG
#include "GuiWindow.h"
#include "EditorManager.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
WindowBase::WindowBase(EditorManager* editorManager)
	: m_editor_manager(editorManager)
	, m_window(nullptr)
	, m_need_update(false)
	, m_is_delete(false)
{
}

/**
* @brief ウィンドウ削除
*/
void WindowBase::DeleteWindow()
{
	if (m_window != nullptr)
	{
		m_editor_manager->GetGuiManager()->DeleteGuiItem(m_window);
		m_window = nullptr;
		m_need_update = false;
	}
}

}// !namespace HaraProject::Framework {
#endif // _DEBUG