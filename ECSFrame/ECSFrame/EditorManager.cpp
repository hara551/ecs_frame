#ifdef _DEBUG
#include <memory>
#include <unordered_map>
#include <vector>
#include <set>

#include "GuiManager.h"
#include "EditorManager.h"
#include "EntityManager.h"
#include "ComponentDataManager.h"
#include "ComponentDataChunk.h"
#include "SystemManager.h"
#include "EditDataUtil.h"
#include "WorldManager.h"

#include "WorldWindow.h"
#include "DetailsWindow.h"
#include "TextInputDialog.h"
#include "DebugSystemOptionWindow.h"

#include "EntityTypes.h"
#include "CameraSystemBase.h"
#include "SpriteRendererSystem.h"
#include "ModelRendererSystem.h"
#include "CameraManagerSystem.h"
#include "CameraDccSystem.h"
#include "GridRendererSystem.h"
#include "CollisionRendererSystem.h"
#include "MovementSystem.h"
#include "BoxCollisionSystem.h"
#include "GeometryRendererSystem.h"
#include "Circle2DCollisionSystem.h"

#include "ThreadPoolManager.h"
#include "UITextureManager.h"
#include "ModelManager.h"
#include "SoundManager.h"

#include "Sprite.h"
#include "ComponentDataUtil.h"
#include "Input.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
EditorManager::EditorManager()
	: m_gui_manager(nullptr)
	, m_select_entity_id(0)
	, m_edit_world_name("City_Sample")
	, m_edit_mode(Edit)
	, m_edit_data_manager(nullptr)
	, m_is_draw_gui(true)
{
	m_edit_data_manager = new EditDataManager();
	m_subscene_manager = new SubsceneManager(this);
	InitEditor();
}

/**
* @brief デストラクタ
*/
EditorManager::~EditorManager()
{
	delete m_edit_data_manager;
	delete m_subscene_manager;

	UninitEditor();
}

/**
* @brief 初期化処理
*/
void EditorManager::InitEditor()
{
	m_component_data_manager = new ComponentDataManager();
	m_entity_manager = new EntityManager(m_component_data_manager);
	m_system_manager = new SystemManager(m_entity_manager, m_component_data_manager);

	LoadWorld();

	RegisterEditorSystems();

	m_gui_manager = std::make_shared<GuiManager>();

	// ウィンドウ作成
	RegisterWindow<WorldWindow>(WORLD_WINDOW_TITLE);
	RegisterWindow<DetailsWindow>(DETAILS_WINDOW_TITLE);
	RegisterWindow<TextInputDialog>(TEXT_INPUT_DIALOG_TITLE);
	RegisterWindow<DebugSystemOptionWindow>(DEBUG_SYSTEM_OPTION_WINDOW_TITLE);
}

/**
* @brief 終了処理
*/
void EditorManager::UninitEditor()
{
	if (!m_copy_entity_data.empty())
	{
		ReleaceEntityValueHandler(m_copy_entity_data);
	}

	if (!m_copy_entity_data.empty())
	{
		for (auto& copy_entity_data : m_copy_subscene_data)
		{
			if (!copy_entity_data.empty())
			{
				m_edit_data_manager->ReleaceLoadedEntityData(copy_entity_data);
			}
		}
	}

	delete m_system_manager;
	delete m_entity_manager;
	delete m_component_data_manager;

	for (auto& window : m_name_to_window)
	{
		if (window.second != nullptr)
		{
			delete window.second;
		}
	}
}

/**
* @brief エディター更新
*/
void EditorManager::UpdateEditor(float deltaTime)
{
	// GUI表示非表示切り替え
	if (IsKeyPress(VK_SHIFT) && IsKeyTrigger(VK_RETURN))
	{
		m_is_draw_gui = !m_is_draw_gui;
	}

	// 透視投影と平行投影を切り替え
	CameraManagerSystem* camera_manager = reinterpret_cast<CameraManagerSystem*>(
		m_system_manager->FindSystem(CameraManagerSystem::CAMERA_MANAGER_SYSTEM)
		);
	CameraSystemBase* main_camera = camera_manager->GetCamera(CameraManagerSystem::MainCamera);
	if (IsKeyPress(VK_SHIFT) && IsKeyTrigger('I'))
	{
		main_camera->SetIs3D(!main_camera->Is3D());
	}

	// 選択しているエンティティのコリジョンの選択表示ON
	if (m_entity_manager->HasComponentData(m_select_entity_id, ComponentMask<CollisionBox>::bit))
	{
		CollisionBox* box = reinterpret_cast<CollisionBox*>(m_entity_manager->GetComponentData(m_select_entity_id, ComponentMask<CollisionBox>::bit));
		box->isSelect = true;
	}


	for (auto& window : m_name_to_window)
	{
		if (window.second != nullptr)
		{
			if (window.second->IsDlelete())
			{
				window.second->DeleteWindow();
				window.second->SetIsDelete(false);
			}

			// 更新が必要なウィンドウのみ更新
			if (window.second->NeedUpdate())
			{
				window.second->UpdateWindow();
			}
		}
	}
	
	if (IsKeyPress(VK_CONTROL) && IsKeyPress(VK_SHIFT) && IsKeyTrigger('C'))
	{
		CopySelectEntity();
		WorldWindow* world_window = reinterpret_cast<WorldWindow*>(GetWindow(WORLD_WINDOW_TITLE));
		world_window->SetNeedUpdate(true);
	}
	if (IsKeyPress(VK_CONTROL) && IsKeyPress(VK_SHIFT) && IsKeyTrigger('V'))
	{
		PasteEntity();
		WorldWindow* world_window = reinterpret_cast<WorldWindow*>(GetWindow(WORLD_WINDOW_TITLE));
		world_window->SetNeedUpdate(true);
	}
	if (IsKeyPress(VK_CONTROL) && IsKeyTrigger('R'))
	{
		ReloadResource();
		WorldWindow* world_window = reinterpret_cast<WorldWindow*>(GetWindow(WORLD_WINDOW_TITLE));
		DetailsWindow* details_window = reinterpret_cast<DetailsWindow*>(GetWindow(DETAILS_WINDOW_TITLE));
		world_window->SetNeedUpdate(true);
		details_window->SetNeedUpdate(true);
	}

	m_subscene_manager->UpdateSubScenesTransform();

	if (m_edit_mode == Edit)
	{
		m_component_data_manager->CheckChunkEntitiesVersion();
		m_system_manager->UpdataSystems(deltaTime);
	}
}

/**
* @brief ECS要素をリセット
*/
void EditorManager::ResetECS()
{
	delete m_system_manager;
	delete m_entity_manager;
	delete m_component_data_manager;

	m_subscene_manager->CleanUpSubscenes();

	m_component_data_manager = new ComponentDataManager();
	m_entity_manager = new EntityManager(m_component_data_manager);
	m_system_manager = new SystemManager(m_entity_manager, m_component_data_manager);

	RegisterEditorSystems();
}

/**
* @brief エディターで使用するシステムを登録
*/
void EditorManager::RegisterEditorSystems()
{
	// 描画
	m_system_manager->AddRenderSystem<SpriteRenderSystem>(SystemManager::UI, false,
		SpriteRenderSystem::SPRITE_RENDERER_SYSTEM);
	m_system_manager->AddRenderSystem<ModelRendererSystem>(SystemManager::Object, false,
		ModelRendererSystem::MODEL_RENDERER_SYSTEM);
	m_system_manager->AddRenderSystem<GridRendererSystem>(SystemManager::Object, true,
		GridRendererSystem::GRID_RENDERER_SYSTEM);
	m_system_manager->AddRenderSystem<CollisionRendererSystem>(SystemManager::Object, true,
		CollisionRendererSystem::COLLISION_RENDERER_SYSTEM);
	m_system_manager->AddRenderSystem<GeometryRendererSystem>(SystemManager::Object, false,
		GeometryRendererSystem::GEOMETRY_RENDER_SYSTEM);
	
	// 物理
	m_system_manager->AddSystem<BoxCollisionSystem>(SystemManager::UpdateProcessType_Physics, false,
		BoxCollisionSystem::BOX_COLLISION_SYSTEM);

	// カメラ
	m_system_manager->AddSystem<CameraManagerSystem>(SystemManager::UpdateProcessType_None, true, 
		CameraManagerSystem::CAMERA_MANAGER_SYSTEM);
	// メインカメラに編集用カメラを設定
	CameraManagerSystem* camera_manager = reinterpret_cast<CameraManagerSystem*>(
		m_system_manager->FindSystem(CameraManagerSystem::CAMERA_MANAGER_SYSTEM)
		);
	camera_manager->RegisterCamera<CameraDccSystem>(CameraDccSystem::CAMERA_DCC_SYSTEM);
	camera_manager->ChangeCamera(CameraManagerSystem::MainCamera, CameraDccSystem::CAMERA_DCC_SYSTEM);
}

/**
* @brief エディター描画
*/
void EditorManager::DrawEditor()
{
	if (m_edit_mode == Edit)
	{
		m_system_manager->UpdateRenderSystems();
	}

	if (m_is_draw_gui)
	{
		m_gui_manager->DrawGUI();
	}
}

/**
* @brief 編集モードを変更
* @param[in] editMode 編集モード
*/
void EditorManager::ChangeEditMode(EditMode editMode)
{
	if (m_edit_mode == editMode)return;

	switch (editMode)
	{
	case Edit:
		WorldManager::Instance().ReleaseAllWorlds();
		LoadWorld();
		break;
	case Play:
		SaveWorld();
		WorldManager::Instance().ActivateWorld(m_edit_world_name, WorldActivateHandle::Change, false);
		//ロード後に実行中のワールドのＥＣＳをEditorManagerにセットできたら良い
		break;
	}
	SetEditMode(editMode);
}

/**
* @brief ワールドをロード
*/
void EditorManager::LoadWorld()
{
	// サブシーンごとのエンティティデータを読み込み
	std::unordered_map<std::string, EntityDataList> subscene_to_entity_datas = 
		m_edit_data_manager->LoadWorldDataForEditor(m_edit_world_name);

	// サブシーンごとのトランスフォームを読み込み
	std::unordered_map<std::string, Transform> subscene_to_transform = 
		m_edit_data_manager->LoadSubscenesTransform(m_edit_world_name);

	// サブシーンごとに処理
	for (const auto& [subscene_name, entity_datas] : subscene_to_entity_datas)
	{
		// エンティティデータごとに処理
		std::vector<uint32_t> entities{};
		for (const auto& entity_data : entity_datas)
		{
			// 読み込んだデータを基にエンティティを作成
			entities.push_back(m_entity_manager->CreateLoadedEntity(entity_data));

			// エンティティ作成に使用したデータを解放
			m_edit_data_manager->ReleaceLoadedEntityData(entity_data);
		}
		// サブシーンを作成
		m_subscene_manager->AddSubscene(subscene_name, subscene_to_transform[subscene_name], entities);
	}

	// 必要なリソースをロード
	ReloadResource();
}

void EditorManager::ReloadResource()
{
	// 必要なテクスチャをロード
	std::set<std::string> texture_names = GetNeedsTextureNames(m_component_data_manager);
	for (const auto& texture_name : texture_names)
	{
		UITextureManager::Instance().LoadTexture(texture_name);
	}
	// 必要なモデルをロード
	std::set<std::string> model_names = GetNeedsModelNames(m_component_data_manager);
	for (const auto& model_name : model_names)
	{
		ModelManager::Instance().LoadModel(model_name);
	}
	// 必要なサウンドをロード
	std::unordered_map<SoundManager::SoundType, std::vector<std::string>> sound_names
		= m_edit_data_manager->LoadSoundNames(m_edit_world_name);
	for (const auto& [type, names] : sound_names)
	{
		for (const auto& name : names)
		{
			SoundManager::Instance().LoadSoundFile(type, name);
		}
	}

	// スプライトを持つエンティティにテクスチャをセット
	ComponentBits sprite_bit = ComponentMask<Sprite>::bit;
	std::vector<ComponentDataChunk*> sprite_chunks = m_component_data_manager->FindChunks(sprite_bit);
	for (auto& chunk : sprite_chunks)
	{
		Sprite* sprite = reinterpret_cast<Sprite*>(chunk->CalculateComponentDataPointer(sprite_bit, 0));
		uint32_t num_entities = chunk->GetNumEntities();
		for (int i = 0; i < num_entities; ++i)
		{
			if (!sprite->IsAble() || sprite == nullptr)
			{
				++sprite;
				continue;
			}
			sprite->texture = UITextureManager::Instance().FindTexture(sprite->textureName);
			++sprite;
		}
	}
	// モデルハンドルを持つエンティティにモデルをセット
	ComponentBits model_handle_bit = ComponentMask<ModelHandle>::bit;
	std::vector<ComponentDataChunk*> model_handle_chunks = m_component_data_manager->FindChunks(model_handle_bit);
	for (auto& chunk : model_handle_chunks)
	{
		ModelHandle* model_handle = reinterpret_cast<ModelHandle*>(chunk->CalculateComponentDataPointer(model_handle_bit, 0));
		uint32_t num_entities = chunk->GetNumEntities();
		for (int i = 0; i < num_entities; ++i)
		{
			if (!model_handle->IsAble() || model_handle == nullptr)
			{
				++model_handle;
				continue;
			}
			model_handle->model = ModelManager::Instance().FindModel(model_handle->modelName);
			++model_handle;
		}
	}
}

/**
* @brief サブシーンをロード
* @param[in] subsceneName サブシーン名
*/
void EditorManager::LoadSubscene(std::string subsceneName)
{
	// サブシーンの全エンティティをロード
	EntityDataList entity_datas = m_edit_data_manager->LoadSubSceneData(subsceneName);

	// ロードしたデータを基にエンティティを作成
	std::vector<uint32_t> entity_ids{};
	for (auto& entity : entity_datas)
	{
		entity_ids.push_back(m_entity_manager->CreateLoadedEntity(entity));
	}
	// サブシーンを追加
	m_subscene_manager->AddSubscene(subsceneName, Transform(), entity_ids);

	// 使用済みのデータを解放
	for (auto& entity_data : entity_datas)
	{
		m_edit_data_manager->ReleaceLoadedEntityData(entity_data);
	}
}

/**
* @brief サブシーンを作成
* @param[in] subsceneName サブシーン名
*/
void EditorManager::CreateSubsceen(std::string subsceneName)
{
	m_subscene_manager->AddSubscene(subsceneName);
}

/**
* @brief ワールドをセーブ
*/
void EditorManager::SaveWorld()
{
	m_edit_data_manager->SaveWorldData(
		m_edit_world_name,
		m_entity_manager,
		m_subscene_manager->GetSubsceneDatas()
	);
}

/**
* @brief サブシーンをセーブ
* @param[in] subSceneName サブシーン名
*/
void EditorManager::SaveSubscene(std::string subSceneName)
{
	m_edit_data_manager->SaveSubsceneData(
		m_select_subscene_name,
		m_entity_manager,
		m_subscene_manager->GetSubsceneDatas()[subSceneName]
	);
}

/**
* @brief 空のエンティティを作成
*/
void EditorManager::CreateEmptyEntity()
{
	uint32_t entity_id = m_entity_manager->CreateEntityEmpty();
	m_subscene_manager->AddEntityToSubscene(m_select_subscene_name, entity_id);
}

/**
* @brief ワールド名変更
* @param[in] newName 新ワールド名
*/
void EditorManager::RenameWorld(std::string newName)
{
	m_edit_world_name = newName;
}

/**
* @brief 選択中のサブシーン名を変更
* @param[in] newName 新サブシーン名
*/
void EditorManager::RenameSubScene(std::string newName)
{
	// 名前を変更
	m_subscene_manager->RenameSubscene(m_select_subscene_name, newName);
	// 選択中のサブシーン名も変更
	m_select_subscene_name = newName;
}

/**
* @brief サブシーンの移動をエンティティに反映する
*/
void EditorManager::UpdateSubSceneTransforms()
{
	m_subscene_manager->UpdateSubScenesTransform();
}

/**
* @brief 選択中のサブシーン内のエンティティを全てコピーする
*/
void EditorManager::CopySubsceneEntities()
{
	// 以前コピーしたデータを解放
	if (!m_copy_subscene_data.empty())
	{
		for (auto& copy_entity_data : m_copy_subscene_data)
		{
			if (!copy_entity_data.empty())
			{
				m_edit_data_manager->ReleaceLoadedEntityData(copy_entity_data);
			}
		}
	}

	std::vector<uint32_t> entities = m_subscene_manager->GetEntitiesBySubscene()[m_select_subscene_name];
	for (const auto& entity : entities)
	{
		m_copy_subscene_data.push_back(m_entity_manager->GetEntityData(entity));
	}
}

/**
* @brief コピー中のサブシーンのエンティティを選択中のサブシーン内に作成する
*/
void EditorManager::PasteSubsceneEntities()
{
	if (m_copy_subscene_data.empty())return;

	for (auto& copy_entity_data : m_copy_subscene_data)
	{
		// コピーしたデータを基にエンティティを作成
		uint32_t id = m_entity_manager->CreateLoadedEntity(copy_entity_data);
		// サブシーンに追加
		m_subscene_manager->AddEntityToSubscene(m_select_subscene_name, id);
	}
}

/**
* @brief 選択中のエンティティのデータをコピーして保持する
*/
void EditorManager::CopySelectEntity()
{
	if (!m_copy_entity_data.empty())
	{
		ReleaceEntityValueHandler(m_copy_entity_data);
	}
	m_copy_entity_data = m_entity_manager->GetEntityData(m_select_entity_id);
}

/**
* @brief コピー中のデータでエンティティを作成
*/
void EditorManager::PasteEntity()
{
	// コピーしたデータを基にエンティティを作成
	uint32_t id = m_entity_manager->CreateLoadedEntity(m_copy_entity_data);
	// サブシーンに追加
	m_subscene_manager->AddEntityToSubscene(m_select_subscene_name, id);
}

/**
* @brief 選択中のサブシーンを削除
*/
void EditorManager::DeleteSelectSubScene()
{
	m_subscene_manager->DeleteSubscene(m_select_subscene_name);
}

/**
* @brief 選択中のエンティティを削除
*/
void EditorManager::DeleteSelectEntity()
{
	// エンティティを削除
	m_entity_manager->DeleteEntity(m_select_entity_id);
	// サブシーンからも削除
	m_subscene_manager->RemoveEntityFromSubscene(m_select_entity_id);
}

/**
* @brief GUIマネージャー取得
*/
std::shared_ptr<GuiManager> EditorManager::GetGuiManager()
{
	return m_gui_manager;
}

/**
* @brief 選択中サブシーン設定
* @param[in] name サブシーン名
*/
void EditorManager::SetSelectSubScene(std::string name)
{
	m_select_subscene_name = name;
}

/**
* @brief 選択中サブシーン名取得
*/
std::string EditorManager::GetSelectSubScene()
{
	return m_select_subscene_name;
}

/**
* @brief 選択中エンティティ設定
*/
void EditorManager::SetSelectEntityId(uint32_t id)
{
	m_select_entity_id = id;
}

/**
* @brief 選択中エンティティID取得
*/
uint32_t EditorManager::GetSelectEntityId()
{
	return m_select_entity_id;
}

/**
* @brief ウィンドウ取得
* @param[in] windowName ウィンドウ名
*/
WindowBase* EditorManager::GetWindow(std::string windowName)
{
	if (m_name_to_window.contains(windowName))
	{
		return m_name_to_window[windowName];
	}
	return nullptr;
}

/**
* @brief エンティティマネージャー取得
*/
EntityManager* EditorManager::GetEntityManager()
{
	return m_entity_manager;
}

/**
* @brief コンポーネントデータマネージャー取得
*/
ComponentDataManager* EditorManager::GetComponentDataManager()
{
	return m_component_data_manager;
}

/**
* @brief システムマネージャー取得
*/
SystemManager* EditorManager::GetSystemManager()
{
	return m_system_manager;
}

/**
* @brief 編集中のワールド名を取得
*/
std::string EditorManager::GetEditWorldName()
{
	return m_edit_world_name;
}
}// !namespace HaraProject::Framework
#endif // _DEBUG