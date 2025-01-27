#ifdef _DEBUG

#include "imgui.h"

#include "EditorManager.h"
#include "DetailsWindow.h"
#include "GuiWindow.h"
#include "Defines.h"
#include "EntityManager.h"
#include "EditDataUtil.h"
#include "TextInputDialog.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
DetailsWindow::DetailsWindow(EditorManager* editorManager)
	: WindowBase(editorManager)
{
	GuiManager* gui_manager = m_editor_manager->GetGuiManager().get();

	// ウィンドウ作成
	m_window = gui_manager->RegisterGuiWindow(DETAILS_WINDOW_TITLE, "id", true,
		ImVec2(DETAILS_WINDOW_POS_X, DETAILS_WINDOW_POS_Y), ImVec2(DETAILS_WINDOW_SIZE_X, DETAILS_WINDOW_SIZE_Y));
}

/**
* @brief 更新処理
*/
void DetailsWindow::UpdateWindow()
{
	DeleteWindow();

	GuiManager* gui_manager = m_editor_manager->GetGuiManager().get();

	// ウィンドウ作成
	m_window = gui_manager->RegisterGuiWindow(DETAILS_WINDOW_TITLE, "id", true,
		ImVec2(DETAILS_WINDOW_POS_X, DETAILS_WINDOW_POS_Y), ImVec2(DETAILS_WINDOW_SIZE_X, DETAILS_WINDOW_SIZE_Y));

	EntityManager* entity_manager = m_editor_manager->GetEntityManager();
	std::unordered_map<ComponentBits, ComponentDataBase*> entity_data_handle{};
	std::unordered_map<std::string, Transform> subscene_to_transform{};

	switch (m_detail_target_type)
	{
	case DetailTargetType_Entity:
		// 各種コンポーネントの表示を追加
		entity_data_handle = entity_manager->GetEntityData(m_editor_manager->GetSelectEntityId());
		for (auto& component : entity_data_handle)
		{
			m_window->AddChild(
				entity_manager->GetComponentData(m_editor_manager->GetSelectEntityId(), 
					component.first)->CreateDetailContent(gui_manager)
			);
		}
		ReleaceEntityValueHandler(entity_data_handle);
		break;
	case DetailTragetType_SubScene:
		m_window->AddChild(
			m_editor_manager->GetSubsceneManager()->GetSubscenesTransform(m_editor_manager->GetSelectSubScene()).CreateDetailContent(gui_manager)
		);
		break;
	case DetailTargetType_World:
		break;
	}

	// コンポーネント追加ダイアログを開くボタン
	m_window->AddChild(
		gui_manager->CreateGuiButton(ADD_COMPONENT_DATA_DIALOG_TITLE, "id",
			[&]()
			{
				TextInputDialog* dialog = reinterpret_cast<TextInputDialog*>(
					m_editor_manager->GetWindow(TEXT_INPUT_DIALOG_TITLE)
					);
				dialog->OpenTextInputDialog(TextInputDialog::InputMode_AddComponentData);
			})
	);
	WindowBase::UpdateWindow();
}

/**
* @brief 詳細表示するターゲットの種類を設定
* @param[in] detailTargetType 詳細表示ターゲットの種類
*/
void DetailsWindow::SetDetailTargetType(DetailTargetType detailTargetType)
{
	m_detail_target_type = detailTargetType;
}

/**
* @brief 詳細表示の種類を指定して更新する
* @param[in] detailTargetType 詳細表示ターゲットの種類
*/
void DetailsWindow::ChangeDetailContent(DetailTargetType detailTargetType)
{
	SetDetailTargetType(detailTargetType);
	SetNeedUpdate(true);
}

}// !namespace HaraProject::Framework {
#endif // _DEBUG