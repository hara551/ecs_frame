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
* @brief �R���X�g���N�^
*/
DebugSystemOptionWindow::DebugSystemOptionWindow(EditorManager* editorManager)
	: WindowBase(editorManager)
{
	GuiManager* gui_manager = m_editor_manager->GetGuiManager().get();

	// �E�B���h�E�쐬
	m_window = gui_manager->RegisterGuiWindow(DEBUG_SYSTEM_OPTION_WINDOW_TITLE, "id", true,
		ImVec2(DEBUG_SYSTEM_OPTION_WINDOW_POS_X, DEBUG_SYSTEM_OPTION_WINDOW_POS_Y), 
		ImVec2(DEBUG_SYSTEM_OPTION_WINDOW_SIZE_X, DEBUG_SYSTEM_OPTION_WINDOW_SIZE_Y));

	UpdateWindow();
}

/**
* @brief �X�V����
*/
void DebugSystemOptionWindow::UpdateWindow()
{
	DeleteWindow();

	GuiManager* gui_manager = m_editor_manager->GetGuiManager().get();

	// �E�B���h�E�쐬
	m_window = gui_manager->RegisterGuiWindow(DEBUG_SYSTEM_OPTION_WINDOW_TITLE, "id", true,
		ImVec2(DEBUG_SYSTEM_OPTION_WINDOW_POS_X, DEBUG_SYSTEM_OPTION_WINDOW_POS_Y),
		ImVec2(DEBUG_SYSTEM_OPTION_WINDOW_SIZE_X, DEBUG_SYSTEM_OPTION_WINDOW_SIZE_Y));

	SystemManager* system_manager = m_editor_manager->GetSystemManager();

	// �I�v�V������\������V�X�e�����擾
	GridRendererSystem* grid_renderer_system = reinterpret_cast<GridRendererSystem*>(
		system_manager->FindSystem(GridRendererSystem::GRID_RENDERER_SYSTEM)
		);
	// �I�v�V����GUI���E�B���h�E�ɒǉ�
	m_window->AddChildren(
		grid_renderer_system->CreateGuiOption(gui_manager)
	);

	WindowBase::UpdateWindow();
}

}//!namespace HaraProject::Framework

#endif // _DEBUG