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
* @brief �R���X�g���N�^
*/
DetailsWindow::DetailsWindow(EditorManager* editorManager)
	: WindowBase(editorManager)
{
	GuiManager* gui_manager = m_editor_manager->GetGuiManager().get();

	// �E�B���h�E�쐬
	m_window = gui_manager->RegisterGuiWindow(DETAILS_WINDOW_TITLE, "id", true,
		ImVec2(DETAILS_WINDOW_POS_X, DETAILS_WINDOW_POS_Y), ImVec2(DETAILS_WINDOW_SIZE_X, DETAILS_WINDOW_SIZE_Y));
}

/**
* @brief �X�V����
*/
void DetailsWindow::UpdateWindow()
{
	DeleteWindow();

	GuiManager* gui_manager = m_editor_manager->GetGuiManager().get();

	// �E�B���h�E�쐬
	m_window = gui_manager->RegisterGuiWindow(DETAILS_WINDOW_TITLE, "id", true,
		ImVec2(DETAILS_WINDOW_POS_X, DETAILS_WINDOW_POS_Y), ImVec2(DETAILS_WINDOW_SIZE_X, DETAILS_WINDOW_SIZE_Y));

	EntityManager* entity_manager = m_editor_manager->GetEntityManager();
	std::unordered_map<ComponentBits, ComponentDataBase*> entity_data_handle{};
	std::unordered_map<std::string, Transform> subscene_to_transform{};

	switch (m_detail_target_type)
	{
	case DetailTargetType_Entity:
		// �e��R���|�[�l���g�̕\����ǉ�
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

	// �R���|�[�l���g�ǉ��_�C�A���O���J���{�^��
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
* @brief �ڍו\������^�[�Q�b�g�̎�ނ�ݒ�
* @param[in] detailTargetType �ڍו\���^�[�Q�b�g�̎��
*/
void DetailsWindow::SetDetailTargetType(DetailTargetType detailTargetType)
{
	m_detail_target_type = detailTargetType;
}

/**
* @brief �ڍו\���̎�ނ��w�肵�čX�V����
* @param[in] detailTargetType �ڍו\���^�[�Q�b�g�̎��
*/
void DetailsWindow::ChangeDetailContent(DetailTargetType detailTargetType)
{
	SetDetailTargetType(detailTargetType);
	SetNeedUpdate(true);
}

}// !namespace HaraProject::Framework {
#endif // _DEBUG