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
* @brief 更新処理
*/
void WorldWindow::UpdateWindow()
{
	// ウィンドウを一度削除
	DeleteWindow();

	GuiManager* gui_manager = m_editor_manager->GetGuiManager().get();

	// ウィンドウ作成
	m_window = gui_manager->RegisterGuiWindow(WORLD_WINDOW_TITLE, "id", true,
		ImVec2(WORLD_WINDOW_POS_X, WORLD_WINDOW_POS_Y), ImVec2(WORLD_WINDOW_SIZE_X, WORLD_WINDOW_SIZE_Y));

	
	m_window->AddChildren(
		// プレイボタン
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
		// ワールド名表示
		gui_manager->CreateGuiSelectable(m_editor_manager->GetEditWorldName(), "id", 
			[gui_manager]()
			{
				// ワールド名クリックでワールドメニューを開く
				gui_manager->GetGuiItem<GuiPopup>(WORLD_MENU_TITLE)->SetShow(true);
			})
	);

	// サブシーンごとのエンティティIDを取得
	std::unordered_map<std::string, std::vector<uint32_t>> subscene_to_entities =
		m_editor_manager->GetSubsceneManager()->GetEntitiesBySubscene();

	EntityManager* entity_manager = m_editor_manager->GetEntityManager();

	//--- エンティティ一覧表示作成
	for (const auto& subscene : subscene_to_entities)
	{
		//--- サブシーン表示アイテム作成
		GuiTreeNode* subscene_node = gui_manager->CreateGuiTreeNode(subscene.first, "id", true,
			[&, gui_manager, subscene]() // 左クリック
			{
				// サブシーン選択
				m_editor_manager->SetSelectSubScene(subscene.first);
				// 詳細ウィンドウにサブシーンを表示
				UpdateDetail(DetailsWindow::DetailTragetType_SubScene);
			},
			[&, gui_manager, subscene]() // 右クリック
			{
				// サブシーン選択
				m_editor_manager->SetSelectSubScene(subscene.first);
				// サブシーンメニューを開く
				gui_manager->GetGuiItem<GuiPopup>(SUBSCENE_MENU_TITLE)->SetShow(true);
			});

		//--- サブシーン内のエンティティ一覧作成
		for (const auto& entity : subscene.second)
		{
			// エンティティ名取得
			EntityName* entity_name = reinterpret_cast<EntityName*>(
				entity_manager->GetComponentData(entity, ComponentMask<EntityName>::bit)
				);
			// 表示に追加
			subscene_node->AddChild(
				gui_manager->CreateGuiSelectable(entity_name->name, "id",
					[&,entity]()
					{
						// 選択時に選択エンティティを変更
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
* @brief ワールドメニュー
*/
void WorldWindow::CreateWorldMenu()
{
	GuiManager* gui_manager = m_editor_manager->GetGuiManager().get();

	// ワールドメニュー作成
	GuiPopup* world_menu =  gui_manager->RegisterGuiPopup(WORLD_MENU_TITLE, "id");

	// メニューに操作を追加
	world_menu->AddChildren(
		// １．編集中のワールドをセーブ
		gui_manager->CreateGuiSelectable("Save World", "id", 
			[&, world_menu]() 
			{ 
				m_editor_manager->SaveWorld();
				world_menu->ClosePopup();
			}),
		// ２．新しくワールドを作成
		gui_manager->CreateGuiSelectable("Create World", "id",
			[&, world_menu]()
			{
				OpenTextInputDialog(TextInputDialog::InputMode_CreateWorld);
				world_menu->ClosePopup();
			}),
		// ３．アセットから指定のワールドをロード
		gui_manager->CreateGuiSelectable("Load World", "id",
			[&, world_menu]()
			{
				OpenTextInputDialog(TextInputDialog::InputMode_LoadWorld);
				world_menu->ClosePopup();
			}),
		// ４．編集中のワールドの名前を変更
		gui_manager->CreateGuiSelectable("Rename World", "id",
			[&, world_menu]()
			{
				OpenTextInputDialog(TextInputDialog::InputMode_RenameWorld);
				world_menu->ClosePopup();
			}),
		// ５．アセットから指定のサブシーンをロード
		gui_manager->CreateGuiSelectable("Load SubScene", "id", 
			[&,world_menu]()
			{
				OpenTextInputDialog(TextInputDialog::InputMode_LoadSubScene);
				world_menu->ClosePopup();
			}),
		// ６. 新しくサブシーンを作成
		gui_manager->CreateGuiSelectable("Create SubScene", "id", 
			[&, world_menu]()
			{
				// サブシーン名を入力するダイアログを立ち上げる
				OpenTextInputDialog(TextInputDialog::InputMode_CreateSubScene);
				world_menu->ClosePopup();
			}),
		// ７．リソースをリロード
		gui_manager->CreateGuiSelectable("Reload Resource", "id", 
			[&, world_menu]()
			{
				m_editor_manager->ReloadResource();
				world_menu->ClosePopup();
			})
	);
}

/**
* @brief サブシーンメニュー
*/
void WorldWindow::CreateSubSceneMenu()
{
	GuiManager* gui_manager = m_editor_manager->GetGuiManager().get();

	// サブシーンメニュー作成
	GuiPopup* subscene_menu = gui_manager->RegisterGuiPopup(SUBSCENE_MENU_TITLE, "id");

	// メニューに操作を追加
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
* @brief テキスト入力ダイアログを開く
* @param[in] inputMode 入力モード
*/
void WorldWindow::OpenTextInputDialog(TextInputDialog::InputMode inputMode)
{
	TextInputDialog* dialog = reinterpret_cast<TextInputDialog*>(
		m_editor_manager->GetWindow(TEXT_INPUT_DIALOG_TITLE)
		);
	dialog->OpenTextInputDialog(inputMode);
}

/**
* @brief 詳細表示を更新する
* @param[in] detailTargetType 詳細表示ターゲットの種類
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