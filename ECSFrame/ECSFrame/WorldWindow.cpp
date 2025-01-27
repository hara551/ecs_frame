#ifdef _DEBUG
#include <string>
#include <unordered_map>
#include <vector>

#include "imgui.h"

#include "WorldWindow.h"
#include "GuiPopup.h"
#include "EditorManager.h"
#include "EntityManager.h"
#include "GuiTreeNode.h"
#include "EntityName.h"
#include "ComponentMask.h"
#include "ComponentRegistry.h"
#include "TextInputDialog.h"
#include "DetailsWindow.h"
#include "GuiManager.h"

namespace HaraProject::Framework {

WorldWindow::WorldWindow(EditorManager* editorManager)
	: WindowBase(editorManager)
{
	CreateWorldMenu();
	CreateSubSceneMenu();
	UpdateWindow();
}

/**
* @brief �X�V����
*/
void WorldWindow::UpdateWindow()
{
	// �E�B���h�E����x�폜
	DeleteWindow();

	GuiManager* gui_manager = m_editor_manager->GetGuiManager().get();

	// �E�B���h�E�쐬
	m_window = gui_manager->RegisterGuiWindow(WORLD_WINDOW_TITLE, "id", true,
		ImVec2(WORLD_WINDOW_POS_X, WORLD_WINDOW_POS_Y), ImVec2(WORLD_WINDOW_SIZE_X, WORLD_WINDOW_SIZE_Y));

	
	m_window->AddChildren(
		// �v���C�{�^��
		gui_manager->CreateGuiButton("Play", "id", 
			[&]()
			{
				if (m_editor_manager->GetEditMode() == EditorManager::Play)
				{
					m_editor_manager->ChangeEditMode(EditorManager::Edit);
				}
				else
				{
					m_editor_manager->ChangeEditMode(EditorManager::Play);
				}

			}),
		// ���[���h���\��
		gui_manager->CreateGuiSelectable(m_editor_manager->GetEditWorldName(), "id", 
			[gui_manager]()
			{
				// ���[���h���N���b�N�Ń��[���h���j���[���J��
				gui_manager->GetGuiItem<GuiPopup>(WORLD_MENU_TITLE)->SetShow(true);
			})
	);

	// �T�u�V�[�����Ƃ̃G���e�B�e�BID���擾
	std::unordered_map<std::string, std::vector<uint32_t>> subscene_to_entities =
		m_editor_manager->GetSubsceneManager()->GetEntitiesBySubscene();

	EntityManager* entity_manager = m_editor_manager->GetEntityManager();

	//--- �G���e�B�e�B�ꗗ�\���쐬
	for (const auto& subscene : subscene_to_entities)
	{
		//--- �T�u�V�[���\���A�C�e���쐬
		GuiTreeNode* subscene_node = gui_manager->CreateGuiTreeNode(subscene.first, "id", true,
			[&, gui_manager, subscene]() // ���N���b�N
			{
				// �T�u�V�[���I��
				m_editor_manager->SetSelectSubScene(subscene.first);
				// �ڍ׃E�B���h�E�ɃT�u�V�[����\��
				UpdateDetail(DetailsWindow::DetailTragetType_SubScene);
			},
			[&, gui_manager, subscene]() // �E�N���b�N
			{
				// �T�u�V�[���I��
				m_editor_manager->SetSelectSubScene(subscene.first);
				// �T�u�V�[�����j���[���J��
				gui_manager->GetGuiItem<GuiPopup>(SUBSCENE_MENU_TITLE)->SetShow(true);
			});

		//--- �T�u�V�[�����̃G���e�B�e�B�ꗗ�쐬
		for (const auto& entity : subscene.second)
		{
			// �G���e�B�e�B���擾
			EntityName* entity_name = reinterpret_cast<EntityName*>(
				entity_manager->GetComponentData(entity, ComponentMask<EntityName>::bit)
				);
			// �\���ɒǉ�
			subscene_node->AddChild(
				gui_manager->CreateGuiSelectable(entity_name->name, "id",
					[&,entity]()
					{
						// �I�����ɑI���G���e�B�e�B��ύX
						m_editor_manager->SetSelectEntityId(entity);
						UpdateDetail(DetailsWindow::DetailTargetType_Entity);
					})
			);
		}
		m_window->AddChild(subscene_node);
	}

	WindowBase::UpdateWindow();
}

/**
* @brief ���[���h���j���[
*/
void WorldWindow::CreateWorldMenu()
{
	GuiManager* gui_manager = m_editor_manager->GetGuiManager().get();

	// ���[���h���j���[�쐬
	GuiPopup* world_menu =  gui_manager->RegisterGuiPopup(WORLD_MENU_TITLE, "id");

	// ���j���[�ɑ����ǉ�
	world_menu->AddChildren(
		// �P�D�ҏW���̃��[���h���Z�[�u
		gui_manager->CreateGuiSelectable("Save World", "id", 
			[&, world_menu]() 
			{ 
				m_editor_manager->SaveWorld();
				world_menu->ClosePopup();
			}),
		// �Q�D�V�������[���h���쐬
		gui_manager->CreateGuiSelectable("Create World", "id",
			[&, world_menu]()
			{
				OpenTextInputDialog(TextInputDialog::InputMode_CreateWorld);
				world_menu->ClosePopup();
			}),
		// �R�D�A�Z�b�g����w��̃��[���h�����[�h
		gui_manager->CreateGuiSelectable("Load World", "id",
			[&, world_menu]()
			{
				OpenTextInputDialog(TextInputDialog::InputMode_LoadWorld);
				world_menu->ClosePopup();
			}),
		// �S�D�ҏW���̃��[���h�̖��O��ύX
		gui_manager->CreateGuiSelectable("Rename World", "id",
			[&, world_menu]()
			{
				OpenTextInputDialog(TextInputDialog::InputMode_RenameWorld);
				world_menu->ClosePopup();
			}),
		// �T�D�A�Z�b�g����w��̃T�u�V�[�������[�h
		gui_manager->CreateGuiSelectable("Load SubScene", "id", 
			[&,world_menu]()
			{
				OpenTextInputDialog(TextInputDialog::InputMode_LoadSubScene);
				world_menu->ClosePopup();
			}),
		// �U. �V�����T�u�V�[�����쐬
		gui_manager->CreateGuiSelectable("Create SubScene", "id", 
			[&, world_menu]()
			{
				// �T�u�V�[��������͂���_�C�A���O�𗧂��グ��
				OpenTextInputDialog(TextInputDialog::InputMode_CreateSubScene);
				world_menu->ClosePopup();
			}),
		// �V�D���\�[�X�������[�h
		gui_manager->CreateGuiSelectable("Reload Resource", "id", 
			[&, world_menu]()
			{
				m_editor_manager->ReloadResource();
				world_menu->ClosePopup();
			})
	);
}

/**
* @brief �T�u�V�[�����j���[
*/
void WorldWindow::CreateSubSceneMenu()
{
	GuiManager* gui_manager = m_editor_manager->GetGuiManager().get();

	// �T�u�V�[�����j���[�쐬
	GuiPopup* subscene_menu = gui_manager->RegisterGuiPopup(SUBSCENE_MENU_TITLE, "id");

	// ���j���[�ɑ����ǉ�
	subscene_menu->AddChildren(
		gui_manager->CreateGuiSelectable("Save SubScene", "id", 
			[&, subscene_menu]()
			{
				m_editor_manager->SaveSubscene(m_editor_manager->GetSelectSubScene()); 
				subscene_menu->ClosePopup();
			}),
		gui_manager->CreateGuiSelectable("Rename", "id", 
			[&, subscene_menu]()
			{
				OpenTextInputDialog(TextInputDialog::InputMode_RenameSubScene);
				m_need_update = true;
				subscene_menu->ClosePopup();
			}),
		gui_manager->CreateGuiSelectable("Delete SubScene", "id",
			[&, subscene_menu]()
			{
				m_editor_manager->DeleteSelectSubScene();
				m_need_update = true;
				subscene_menu->ClosePopup();
			}),
		gui_manager->CreateGuiSelectable("Delete Select Entity", "id",
			[&, subscene_menu]()
			{
				m_editor_manager->DeleteSelectEntity();
				m_need_update = true;
				subscene_menu->ClosePopup();
			}),
		gui_manager->CreateGuiSelectable("Create Empty Entity", "id", 
			[&, subscene_menu]()
			{
				m_editor_manager->CreateEmptyEntity();
				UpdateDetail(DetailsWindow::DetailTargetType_Entity);
				m_need_update = true;
				subscene_menu->ClosePopup();
			}),
		gui_manager->CreateGuiSelectable("Copy Subscene Entities", "id",
			[&, subscene_menu]()
			{
				m_editor_manager->CopySubsceneEntities();
				subscene_menu->ClosePopup();
			}),
		gui_manager->CreateGuiSelectable("Paste Subscene Entities", "id",
			[&, subscene_menu]()
			{
				m_editor_manager->PasteSubsceneEntities();
				m_need_update = true;
				subscene_menu->ClosePopup();
			}),
		gui_manager->CreateGuiSelectable("Copy Select Entity", "id",
			[&, subscene_menu]()
			{
				m_editor_manager->CopySelectEntity();
				subscene_menu->ClosePopup();
			}),
		gui_manager->CreateGuiSelectable("Pasete Entity", "id",
			[&, subscene_menu]()
			{
				m_editor_manager->PasteEntity();
				m_need_update = true;
				subscene_menu->ClosePopup();
			})
	);
}

/**
* @brief �e�L�X�g���̓_�C�A���O���J��
* @param[in] inputMode ���̓��[�h
*/
void WorldWindow::OpenTextInputDialog(TextInputDialog::InputMode inputMode)
{
	TextInputDialog* dialog = reinterpret_cast<TextInputDialog*>(
		m_editor_manager->GetWindow(TEXT_INPUT_DIALOG_TITLE)
		);
	dialog->OpenTextInputDialog(inputMode);
}

/**
* @brief �ڍו\�����X�V����
* @param[in] detailTargetType �ڍו\���^�[�Q�b�g�̎��
*/
void WorldWindow::UpdateDetail(DetailsWindow::DetailTargetType detailTargetType)
{
	DetailsWindow* detail_window = reinterpret_cast<DetailsWindow*>(
		m_editor_manager->GetWindow(DETAILS_WINDOW_TITLE)
		);
	detail_window->ChangeDetailContent(detailTargetType);
}

}// !namespace HaraProject::Framework {
#endif // _DEBUG