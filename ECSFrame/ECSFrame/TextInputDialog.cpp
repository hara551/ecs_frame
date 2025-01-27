#ifdef _DEBUG
#include <functional>

#include "imgui.h"

#include "GuiManager.h"
#include "GuiInputBase.h"
#include "EditorManager.h"
#include "WorldWindow.h"
#include "ComponentRegistry.h"

#include "TextInputDialog.h"
#include "WindowBase.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
* @param[in] editorManager エディターマネージャー
*/
TextInputDialog::TextInputDialog(EditorManager* editorManager)
	: WindowBase(editorManager)
	, m_input_mode(InputMode_None)
	, m_text_input_buffer("Text")
{
}

/**
* @brief 更新処理
*/
void TextInputDialog::UpdateWindow()
{
	DeleteWindow();
	
	GuiManager* gui_manager = m_editor_manager->GetGuiManager().get();

	std::string dialog_title{};
	std::function<void()> action{};

	switch (m_input_mode)
	{
	case InputMode_RenameWorld:
		dialog_title = RENAME_WORLD_DIALOG_TITLE;
		action = [&]()
		{
			// 編集中のワールド名を変更
			m_editor_manager->RenameWorld(std::string(m_text_input_buffer));
			CloseTextInputDialog();
		};
		break;
	case InputMode_RenameSubScene:
		dialog_title = RENAME_SUBSCENE_DIALOG_TITLE;
		action = [&]()
		{
			// 選択中のサブシーン名を変更
			m_editor_manager->RenameSubScene(std::string(m_text_input_buffer));
			CloseTextInputDialog();
		};
		break;
	case InputMode_LoadWorld:
		dialog_title = LOAD_WORLD_DIALOG_TITLE;
		action = [&]()
		{
			// 現在のワールドと入れ替え
			m_editor_manager->ResetECS();
			m_editor_manager->RenameWorld(std::string(m_text_input_buffer));
			m_editor_manager->LoadWorld();
			m_editor_manager->RegisterEditorSystems();
			CloseTextInputDialog();
		};
		break;
	case InputMode_LoadSubScene:
		dialog_title = LOAD_SUBSCENE_DIALOG_TITLE;
		action = [&]()
		{
			m_editor_manager->LoadSubscene(std::string(m_text_input_buffer));
			CloseTextInputDialog();
		};
		break;
	case InputMode_CreateWorld:
		dialog_title = CREATE_WORLD_DIALOG_TITLE;
		action = [&]()
		{
			// 現在のECSをリセットして、ワールド名も変更
			m_editor_manager->ResetECS();
			m_editor_manager->RenameWorld(std::string(m_text_input_buffer));
			CloseTextInputDialog();
		};
		break;
	case InputMode_CreateSubScene:
		dialog_title = CREATE_SUBSCENE_DIALOG_TITLE;
		action = [&]()
		{
			m_editor_manager->CreateSubsceen(std::string(m_text_input_buffer));
			CloseTextInputDialog();
		};
		break;
	case InputMode_AddComponentData:
		dialog_title = ADD_COMPONENT_DATA_DIALOG_TITLE;
		action = [&]()
		{
			EntityManager* entity_manager = m_editor_manager->GetEntityManager();

			ComponentBits component_bit = ComponentRegistry::GetBitByName(m_text_input_buffer);
			entity_manager->AddComponentData(m_editor_manager->GetSelectEntityId(), component_bit);

			DetailsWindow* detail_window = reinterpret_cast<DetailsWindow*>(
				m_editor_manager->GetWindow(DETAILS_WINDOW_TITLE)
				);
			detail_window->ChangeDetailContent(DetailsWindow::DetailTargetType_Entity);

			CloseTextInputDialog();
		};
		break;
	}

	m_window = gui_manager->RegisterGuiWindow(dialog_title, "id", true,
		ImVec2(TEXT_INPUT_DIALOG_POS_X, TEXT_INPUT_DIALOG_POS_Y),
		ImVec2(TEXT_INPUT_DIALOG_SIZE_X, TEXT_INPUT_DIALOG_SIZE_Y));

	m_window->AddChildren(
		gui_manager->CreateGuiInputText("Name", "id", GuiInputBase::Always, m_text_input_buffer),
		gui_manager->CreateGuiButton("Cancel", "id", [&]() { SetIsDelete(true); }),
		gui_manager->CreateGuiButton("OK", "id", action)
	);

	WindowBase::UpdateWindow();
}

/**
* @brief 入力モード設定
* @param[in] inputMode 入力モード
*/
void TextInputDialog::SetInputMode(InputMode inputMode)
{
	m_input_mode = inputMode;
}

/**
* @brief ダイアログを開く
* @param[in] inputMode 入力モード
*/
void TextInputDialog::OpenTextInputDialog(InputMode inputMode)
{
	SetInputMode(inputMode);
	SetNeedUpdate(true);
}

/**
* @brief ダイアログを閉じる
*/
void TextInputDialog::CloseTextInputDialog()
{
	m_editor_manager->GetWindow(WORLD_WINDOW_TITLE)->SetNeedUpdate(true);
	SetIsDelete(true);
}

}// !namespace HaraProject::Framework {
#endif // _DEBUG