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
* @brief �R���X�g���N�^
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
* @brief �f�X�g���N�^
*/
EditorManager::~EditorManager()
{
	delete m_edit_data_manager;
	delete m_subscene_manager;

	UninitEditor();
}

/**
* @brief ����������
*/
void EditorManager::InitEditor()
{
	m_component_data_manager = new ComponentDataManager();
	m_entity_manager = new EntityManager(m_component_data_manager);
	m_system_manager = new SystemManager(m_entity_manager, m_component_data_manager);

	LoadWorld();

	RegisterEditorSystems();

	m_gui_manager = std::make_shared<GuiManager>();

	// �E�B���h�E�쐬
	RegisterWindow<WorldWindow>(WORLD_WINDOW_TITLE);
	RegisterWindow<DetailsWindow>(DETAILS_WINDOW_TITLE);
	RegisterWindow<TextInputDialog>(TEXT_INPUT_DIALOG_TITLE);
	RegisterWindow<DebugSystemOptionWindow>(DEBUG_SYSTEM_OPTION_WINDOW_TITLE);
}

/**
* @brief �I������
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
* @brief �G�f�B�^�[�X�V
*/
void EditorManager::UpdateEditor(float deltaTime)
{
	// GUI�\����\���؂�ւ�
	if (IsKeyPress(VK_SHIFT) && IsKeyTrigger(VK_RETURN))
	{
		m_is_draw_gui = !m_is_draw_gui;
	}

	// �������e�ƕ��s���e��؂�ւ�
	CameraManagerSystem* camera_manager = reinterpret_cast<CameraManagerSystem*>(
		m_system_manager->FindSystem(CameraManagerSystem::CAMERA_MANAGER_SYSTEM)
		);
	CameraSystemBase* main_camera = camera_manager->GetCamera(CameraManagerSystem::MainCamera);
	if (IsKeyPress(VK_SHIFT) && IsKeyTrigger('I'))
	{
		main_camera->SetIs3D(!main_camera->Is3D());
	}

	// �I�����Ă���G���e�B�e�B�̃R���W�����̑I��\��ON
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

			// �X�V���K�v�ȃE�B���h�E�̂ݍX�V
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
* @brief ECS�v�f�����Z�b�g
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
* @brief �G�f�B�^�[�Ŏg�p����V�X�e����o�^
*/
void EditorManager::RegisterEditorSystems()
{
	// �`��
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
	
	// ����
	m_system_manager->AddSystem<BoxCollisionSystem>(SystemManager::UpdateProcessType_Physics, false,
		BoxCollisionSystem::BOX_COLLISION_SYSTEM);

	// �J����
	m_system_manager->AddSystem<CameraManagerSystem>(SystemManager::UpdateProcessType_None, true, 
		CameraManagerSystem::CAMERA_MANAGER_SYSTEM);
	// ���C���J�����ɕҏW�p�J������ݒ�
	CameraManagerSystem* camera_manager = reinterpret_cast<CameraManagerSystem*>(
		m_system_manager->FindSystem(CameraManagerSystem::CAMERA_MANAGER_SYSTEM)
		);
	camera_manager->RegisterCamera<CameraDccSystem>(CameraDccSystem::CAMERA_DCC_SYSTEM);
	camera_manager->ChangeCamera(CameraManagerSystem::MainCamera, CameraDccSystem::CAMERA_DCC_SYSTEM);
}

/**
* @brief �G�f�B�^�[�`��
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
* @brief �ҏW���[�h��ύX
* @param[in] editMode �ҏW���[�h
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
		//���[�h��Ɏ��s���̃��[���h�̂d�b�r��EditorManager�ɃZ�b�g�ł�����ǂ�
		break;
	}
	SetEditMode(editMode);
}

/**
* @brief ���[���h�����[�h
*/
void EditorManager::LoadWorld()
{
	// �T�u�V�[�����Ƃ̃G���e�B�e�B�f�[�^��ǂݍ���
	std::unordered_map<std::string, EntityDataList> subscene_to_entity_datas = 
		m_edit_data_manager->LoadWorldDataForEditor(m_edit_world_name);

	// �T�u�V�[�����Ƃ̃g�����X�t�H�[����ǂݍ���
	std::unordered_map<std::string, Transform> subscene_to_transform = 
		m_edit_data_manager->LoadSubscenesTransform(m_edit_world_name);

	// �T�u�V�[�����Ƃɏ���
	for (const auto& [subscene_name, entity_datas] : subscene_to_entity_datas)
	{
		// �G���e�B�e�B�f�[�^���Ƃɏ���
		std::vector<uint32_t> entities{};
		for (const auto& entity_data : entity_datas)
		{
			// �ǂݍ��񂾃f�[�^����ɃG���e�B�e�B���쐬
			entities.push_back(m_entity_manager->CreateLoadedEntity(entity_data));

			// �G���e�B�e�B�쐬�Ɏg�p�����f�[�^�����
			m_edit_data_manager->ReleaceLoadedEntityData(entity_data);
		}
		// �T�u�V�[�����쐬
		m_subscene_manager->AddSubscene(subscene_name, subscene_to_transform[subscene_name], entities);
	}

	// �K�v�ȃ��\�[�X�����[�h
	ReloadResource();
}

void EditorManager::ReloadResource()
{
	// �K�v�ȃe�N�X�`�������[�h
	std::set<std::string> texture_names = GetNeedsTextureNames(m_component_data_manager);
	for (const auto& texture_name : texture_names)
	{
		UITextureManager::Instance().LoadTexture(texture_name);
	}
	// �K�v�ȃ��f�������[�h
	std::set<std::string> model_names = GetNeedsModelNames(m_component_data_manager);
	for (const auto& model_name : model_names)
	{
		ModelManager::Instance().LoadModel(model_name);
	}
	// �K�v�ȃT�E���h�����[�h
	std::unordered_map<SoundManager::SoundType, std::vector<std::string>> sound_names
		= m_edit_data_manager->LoadSoundNames(m_edit_world_name);
	for (const auto& [type, names] : sound_names)
	{
		for (const auto& name : names)
		{
			SoundManager::Instance().LoadSoundFile(type, name);
		}
	}

	// �X�v���C�g�����G���e�B�e�B�Ƀe�N�X�`�����Z�b�g
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
	// ���f���n���h�������G���e�B�e�B�Ƀ��f�����Z�b�g
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
* @brief �T�u�V�[�������[�h
* @param[in] subsceneName �T�u�V�[����
*/
void EditorManager::LoadSubscene(std::string subsceneName)
{
	// �T�u�V�[���̑S�G���e�B�e�B�����[�h
	EntityDataList entity_datas = m_edit_data_manager->LoadSubSceneData(subsceneName);

	// ���[�h�����f�[�^����ɃG���e�B�e�B���쐬
	std::vector<uint32_t> entity_ids{};
	for (auto& entity : entity_datas)
	{
		entity_ids.push_back(m_entity_manager->CreateLoadedEntity(entity));
	}
	// �T�u�V�[����ǉ�
	m_subscene_manager->AddSubscene(subsceneName, Transform(), entity_ids);

	// �g�p�ς݂̃f�[�^�����
	for (auto& entity_data : entity_datas)
	{
		m_edit_data_manager->ReleaceLoadedEntityData(entity_data);
	}
}

/**
* @brief �T�u�V�[�����쐬
* @param[in] subsceneName �T�u�V�[����
*/
void EditorManager::CreateSubsceen(std::string subsceneName)
{
	m_subscene_manager->AddSubscene(subsceneName);
}

/**
* @brief ���[���h���Z�[�u
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
* @brief �T�u�V�[�����Z�[�u
* @param[in] subSceneName �T�u�V�[����
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
* @brief ��̃G���e�B�e�B���쐬
*/
void EditorManager::CreateEmptyEntity()
{
	uint32_t entity_id = m_entity_manager->CreateEntityEmpty();
	m_subscene_manager->AddEntityToSubscene(m_select_subscene_name, entity_id);
}

/**
* @brief ���[���h���ύX
* @param[in] newName �V���[���h��
*/
void EditorManager::RenameWorld(std::string newName)
{
	m_edit_world_name = newName;
}

/**
* @brief �I�𒆂̃T�u�V�[������ύX
* @param[in] newName �V�T�u�V�[����
*/
void EditorManager::RenameSubScene(std::string newName)
{
	// ���O��ύX
	m_subscene_manager->RenameSubscene(m_select_subscene_name, newName);
	// �I�𒆂̃T�u�V�[�������ύX
	m_select_subscene_name = newName;
}

/**
* @brief �T�u�V�[���̈ړ����G���e�B�e�B�ɔ��f����
*/
void EditorManager::UpdateSubSceneTransforms()
{
	m_subscene_manager->UpdateSubScenesTransform();
}

/**
* @brief �I�𒆂̃T�u�V�[�����̃G���e�B�e�B��S�ăR�s�[����
*/
void EditorManager::CopySubsceneEntities()
{
	// �ȑO�R�s�[�����f�[�^�����
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
* @brief �R�s�[���̃T�u�V�[���̃G���e�B�e�B��I�𒆂̃T�u�V�[�����ɍ쐬����
*/
void EditorManager::PasteSubsceneEntities()
{
	if (m_copy_subscene_data.empty())return;

	for (auto& copy_entity_data : m_copy_subscene_data)
	{
		// �R�s�[�����f�[�^����ɃG���e�B�e�B���쐬
		uint32_t id = m_entity_manager->CreateLoadedEntity(copy_entity_data);
		// �T�u�V�[���ɒǉ�
		m_subscene_manager->AddEntityToSubscene(m_select_subscene_name, id);
	}
}

/**
* @brief �I�𒆂̃G���e�B�e�B�̃f�[�^���R�s�[���ĕێ�����
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
* @brief �R�s�[���̃f�[�^�ŃG���e�B�e�B���쐬
*/
void EditorManager::PasteEntity()
{
	// �R�s�[�����f�[�^����ɃG���e�B�e�B���쐬
	uint32_t id = m_entity_manager->CreateLoadedEntity(m_copy_entity_data);
	// �T�u�V�[���ɒǉ�
	m_subscene_manager->AddEntityToSubscene(m_select_subscene_name, id);
}

/**
* @brief �I�𒆂̃T�u�V�[�����폜
*/
void EditorManager::DeleteSelectSubScene()
{
	m_subscene_manager->DeleteSubscene(m_select_subscene_name);
}

/**
* @brief �I�𒆂̃G���e�B�e�B���폜
*/
void EditorManager::DeleteSelectEntity()
{
	// �G���e�B�e�B���폜
	m_entity_manager->DeleteEntity(m_select_entity_id);
	// �T�u�V�[��������폜
	m_subscene_manager->RemoveEntityFromSubscene(m_select_entity_id);
}

/**
* @brief GUI�}�l�[�W���[�擾
*/
std::shared_ptr<GuiManager> EditorManager::GetGuiManager()
{
	return m_gui_manager;
}

/**
* @brief �I�𒆃T�u�V�[���ݒ�
* @param[in] name �T�u�V�[����
*/
void EditorManager::SetSelectSubScene(std::string name)
{
	m_select_subscene_name = name;
}

/**
* @brief �I�𒆃T�u�V�[�����擾
*/
std::string EditorManager::GetSelectSubScene()
{
	return m_select_subscene_name;
}

/**
* @brief �I�𒆃G���e�B�e�B�ݒ�
*/
void EditorManager::SetSelectEntityId(uint32_t id)
{
	m_select_entity_id = id;
}

/**
* @brief �I�𒆃G���e�B�e�BID�擾
*/
uint32_t EditorManager::GetSelectEntityId()
{
	return m_select_entity_id;
}

/**
* @brief �E�B���h�E�擾
* @param[in] windowName �E�B���h�E��
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
* @brief �G���e�B�e�B�}�l�[�W���[�擾
*/
EntityManager* EditorManager::GetEntityManager()
{
	return m_entity_manager;
}

/**
* @brief �R���|�[�l���g�f�[�^�}�l�[�W���[�擾
*/
ComponentDataManager* EditorManager::GetComponentDataManager()
{
	return m_component_data_manager;
}

/**
* @brief �V�X�e���}�l�[�W���[�擾
*/
SystemManager* EditorManager::GetSystemManager()
{
	return m_system_manager;
}

/**
* @brief �ҏW���̃��[���h�����擾
*/
std::string EditorManager::GetEditWorldName()
{
	return m_edit_world_name;
}
}// !namespace HaraProject::Framework
#endif // _DEBUG