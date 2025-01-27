#ifdef _DEBUG

#include "imgui.h"

#include "DebugSystemOptionWindow.h"
#include "WindowBase.h"
#include "GuiManager.h"
#include "EditorManager.h"
#include "SystemManager.h"
#include "GridRendererSystem.h"

namespace HaraProject::Framework {
/**
* @brief コンストラクタ
*/
DebugSystemOptionWindow::DebugSystemOptionWindow(EditorManager* editorManager)
	: WindowBase(editorManager)
{
	GuiManager* gui_manager = m_editor_manager->GetGuiManager().get();

	// ウィンドウ作成
	m_window = gui_manager->RegisterGuiWindow(DEBUG_SYSTEM_OPTION_WINDOW_TITLE, "id", true,
		ImVec2(DEBUG_SYSTEM_OPTION_WINDOW_POS_X, DEBUG_SYSTEM_OPTION_WINDOW_POS_Y), 
		ImVec2(DEBUG_SYSTEM_OPTION_WINDOW_SIZE_X, DEBUG_SYSTEM_OPTION_WINDOW_SIZE_Y));

	UpdateWindow();
}

/**
* @brief 更新処理
*/
void DebugSystemOptionWindow::UpdateWindow()
{
	DeleteWindow();

	GuiManager* gui_manager = m_editor_manager->GetGuiManager().get();

	// ウィンドウ作成
	m_window = gui_manager->RegisterGuiWindow(DEBUG_SYSTEM_OPTION_WINDOW_TITLE, "id", true,
		ImVec2(DEBUG_SYSTEM_OPTION_WINDOW_POS_X, DEBUG_SYSTEM_OPTION_WINDOW_POS_Y),
		ImVec2(DEBUG_SYSTEM_OPTION_WINDOW_SIZE_X, DEBUG_SYSTEM_OPTION_WINDOW_SIZE_Y));

	SystemManager* system_manager = m_editor_manager->GetSystemManager();

	// オプションを表示するシステムを取得
	GridRendererSystem* grid_renderer_system = reinterpret_cast<GridRendererSystem*>(
		system_manager->FindSystem(GridRendererSystem::GRID_RENDERER_SYSTEM)
		);
	// オプションGUIをウィンドウに追加
	m_window->AddChildren(
		grid_renderer_system->CreateGuiOption(gui_manager)
	);

	WindowBase::UpdateWindow();
}

}//!namespace HaraProject::Framework

#endif // _DEBUG