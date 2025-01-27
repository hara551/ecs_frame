
#include <string>
#include <chrono>

//#include "EntityTypes.h"
#include "WorldBase.h"
#include "ComponentDataManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

#include "EditDataManager.h"
#include "ThreadPoolManager.h"
#include "UITextureManager.h"
#include "ModelManager.h"
#include "SoundManager.h"
#include "ComponentDataUtil.h"
#include "ComponentMask.h"
#include "ComponentDataChunk.h"
#include "Sprite.h"

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

#include "Input.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
WorldBase::WorldBase(std::string name)
	: m_world_name(name)
	, m_num_resource_loading(-1)
	, m_entity_manager(nullptr)
	, m_component_data_manager(nullptr)
	, m_system_manager(nullptr)
	, m_edit_data_loder(nullptr)
{
	InitWorld();
}

/**
* @brief デストラクタ
*/
WorldBase::~WorldBase()
{
	UninitWorld();
}

/**
* @brief ワールド更新処理
*/
void WorldBase::UpdateWorld(float deltaTime)
{
	m_component_data_manager->CheckChunkEntitiesVersion();
	m_system_manager->UpdataSystems(deltaTime);
}

/**
* @brief ワールド描画処理
*/
void WorldBase::DrawWorld()
{
	m_system_manager->UpdateRenderSystems();
}

/**
* @brief ワールド名取得
*/
std::string WorldBase::GetName()
{
	return m_world_name;
}

/**
* @brief ロードが完了したか
*/
bool WorldBase::IsCompleteLoad()
{
	return m_num_resource_loading == 0;
}

/**
* @brief ワールド初期化処理
*/
void WorldBase::InitWorld()
{
	m_component_data_manager = new ComponentDataManager();
	m_entity_manager = new EntityManager(m_component_data_manager);
	m_system_manager = new SystemManager(m_entity_manager, m_component_data_manager);
	m_edit_data_loder = new EditDataManager();

	RegisterWorldSystems();

	CreateEntities();
	LoadWorldResources();
}

/**
* @brief ワールド終了処理
*/
void WorldBase::UninitWorld()
{
	delete m_edit_data_loder;
	delete m_system_manager;
	delete m_entity_manager;
	delete m_component_data_manager;
}

/**
* @brief 既定のシステムを登録
*/
void WorldBase::RegisterWorldSystems()
{
	// 描画
	m_system_manager->AddRenderSystem<SpriteRenderSystem>(SystemManager::UI, false,
		SpriteRenderSystem::SPRITE_RENDERER_SYSTEM);
	m_system_manager->AddRenderSystem<ModelRendererSystem>(SystemManager::Object, false,
		ModelRendererSystem::MODEL_RENDERER_SYSTEM);
	m_system_manager->AddRenderSystem<CollisionRendererSystem>(SystemManager::Object, true,
		CollisionRendererSystem::COLLISION_RENDERER_SYSTEM);
	m_system_manager->AddRenderSystem<GeometryRendererSystem>(SystemManager::Object, false,
		GeometryRendererSystem::GEOMETRY_RENDER_SYSTEM);

	// 物理
	m_system_manager->AddSystem<MovementSystem>(SystemManager::UpdateProcessType_Physics, false,
		MovementSystem::MOVEMENT_SYSTEM);
	m_system_manager->AddSystem<BoxCollisionSystem>(SystemManager::UpdateProcessType_Physics, false,
		BoxCollisionSystem::BOX_COLLISION_SYSTEM);
	m_system_manager->AddSystem<Circle2DCollisionSystem>(SystemManager::UpdateProcessType_Physics, false,
		Circle2DCollisionSystem::CIRCLE_2D_COLLISION_SYSTEM);

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
* @brief ワールドのエンティティを全て作成
*/
void WorldBase::CreateEntities()
{
	// ワールドのエンティティデータを読み込み
	std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>> world_entity_datas
		= m_edit_data_loder->LoadWorldData(m_world_name);

	for (auto& entity_data : world_entity_datas)
	{
		// エンティティを作成
		m_entity_manager->CreateLoadedEntity(entity_data);
		// 読み込みの過程で使用したデータを解放
		m_edit_data_loder->ReleaceLoadedEntityData(entity_data);
	}
}

/**
* @brief ワールドに必要なリソースをロード
*/
void WorldBase::LoadWorldResources()
{
	// 必要なリソース名を取得
	std::set<std::string> need_texture_names = GetNeedsTextureNames(m_component_data_manager);
	std::set<std::string> need_model_names = GetNeedsModelNames(m_component_data_manager);
	std::unordered_map<SoundManager::SoundType, std::vector<std::string>> need_sound_names
		= m_edit_data_loder->LoadSoundNames(m_world_name);

	// ロードするリソース数を保存
	m_num_resource_loading = need_texture_names.size() + need_model_names.size() + 
		need_sound_names[SoundManager::SE].size() + need_sound_names[SoundManager::BGM].size();
	
	// テクスチャをロード
	for (const auto& texture_name : need_texture_names)
	{
		// 非同期ロードを依頼
		ThreadPoolManager::Instance().Enqueue(ThreadPoolManager::ProcessType::Load,
			[&, texture_name]()
			{
				if (UITextureManager::Instance().LoadTexture(texture_name))
				{
					{
						// アクセスをロック
						std::lock_guard<std::mutex> lock(m_loaded_sign_mutex);

						// ロードが完了したらロード中リソース数をデクリメント
						--m_num_resource_loading;

						// 全てのロードが完了していたら
						if (IsCompleteLoad())
						{
							// エンティティにリソースをセットする
							SettingResourcesToEntity();
						}
					}
				}
			});
	}
	// モデルをロード
	for (const auto& model_name : need_model_names)
	{
		// 非同期ロードを依頼
		ThreadPoolManager::Instance().Enqueue(ThreadPoolManager::ProcessType::Load,
			[&, model_name]()
			{
				if (ModelManager::Instance().LoadModel(model_name))
				{
					{
						// アクセスをロック
						std::lock_guard<std::mutex> lock(m_loaded_sign_mutex);

						// ロードが完了したらロード中リソース数をデクリメント
						--m_num_resource_loading;
					
						// 全てのロードが完了していたら
						if (IsCompleteLoad())
						{
							// エンティティにリソースをセットする
							SettingResourcesToEntity();
						}
					}
				}
			});
	}
	// サウンドをロード
	for (const auto& [sound_type, sound_names] : need_sound_names)
	{
		for (const auto& sound_name : sound_names)
		{
			// 非同期ロードを依頼
			ThreadPoolManager::Instance().Enqueue(ThreadPoolManager::ProcessType::Load,
				[&, sound_type, sound_names]()
				{
					if (SoundManager::Instance().LoadSoundFile(sound_type, sound_name))
					{
						{
							// アクセスをロック
							std::lock_guard<std::mutex> lock(m_loaded_sign_mutex);

							// ロードが完了したらロード中リソース数をデクリメント
							--m_num_resource_loading;

							// 全てのロードが完了していたら
							if (IsCompleteLoad())
							{
								// エンティティにリソースをセットする
								SettingResourcesToEntity();
							}
						}
					}
				});
		}
	}
}

/**
* @brief リソースを必要なエンティティにセットする
*/
void WorldBase::SettingResourcesToEntity()
{
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
	// モデルハンドルを持つエンティティにテクスチャをセット
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

} // !namespace HaraProject::Framework