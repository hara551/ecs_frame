
#include "SystemManager.h"
#include "SystemRegistry.h"
#include "SystemBase.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
* @param[in] entityOperator エンティティ操作用
* @param[in] chunkProvider チャンク取得用
*/
SystemManager::SystemManager(IEntityOperator* entityOperator, IChunkProvider* chunkProvider)
	: m_entity_operator(entityOperator), m_chunk_provider(chunkProvider)
{
	// レイヤー分のサイズを確保
	m_systems.resize(MAX_PROCESS_TYPE);
	m_shared_systems.resize(MAX_PROCESS_TYPE);
	m_render_systems.resize(MAX_DRAW_LAYER);
	m_shared_render_systems.resize(MAX_DRAW_LAYER);
}


/**
* @brief デストラクタ
*/
SystemManager::~SystemManager()
{
	ReleaseSharedSystem();
}

/**
* @brief 全システム更新
*/
void SystemManager::UpdataSystems(float deltaTime)
{
	for (int layer = 0; layer < MAX_PROCESS_TYPE; ++layer)
	{
		for (const auto& shared_system : m_shared_systems[layer])
		{
			shared_system.second->UpdateSystem(deltaTime);
		}
		for (const auto& system : m_systems[layer])
		{
			system->UpdateSystem(deltaTime);
		}
	}
}

/**
* @brief 描画システム更新
*/
void SystemManager::UpdateRenderSystems()
{
	for (int layer = 0; layer < MAX_DRAW_LAYER; ++layer)
	{
		for (const auto& shared_system : m_shared_render_systems[layer])
		{
			shared_system.second->UpdateSystem(0);
		}
		for (const auto& system : m_render_systems[layer])
		{
			system->UpdateSystem(0);
		}
	}
}

/**
* @brief システム取得
* @param[in] bit システム名
*/
SystemBase* SystemManager::FindSystem(std::string name)
{
	for (auto& layer : m_shared_systems)
	{
		if (layer.contains(name))
		{
			return layer[name];
		}
	}
	for (auto& layer : m_shared_render_systems)
	{
		if (layer.contains(name))
		{
			return layer[name];
		}
	}
	return nullptr;
}

/**
* @brife システム登録
* @param[in] systemHandle システム登録ハンドル
*/
//void SystemManager::AddSystem(SystemHandle systemHandle)
//{
//	if (systemHandle.isRenderSystem)
//	{
//		if (systemHandle.isShare)
//		{
//			m_shared_render_systems[systemHandle.layer][systemHandle.bit] = 
//				SystemRegistry::Constructor(systemHandle.bit);
//		}
//		else
//		{
//			m_render_systems[systemHandle.layer].push_back(
//				SystemRegistry::UniqueConstructor(systemHandle.bit)
//			);
//		}
//	}
//	else
//	{
//		if (systemHandle.isShare)
//		{
//			m_shared_systems[systemHandle.layer][systemHandle.bit] =
//				SystemRegistry::Constructor(systemHandle.bit);
//		}
//		else
//		{
//			m_systems[systemHandle.layer].push_back(
//				SystemRegistry::UniqueConstructor(systemHandle.bit)
//			);
//		}
//	}
//}

/**
* @brief システム取得
* @param[in] bit システム識別ビット
*/
//SystemBase* SystemManager::FindSystem(SystemBits bit)
//{
//	for (int layer = 0; layer < MAX_PROCESS_TYPE; ++layer)
//	{
//		if(m_shared_systems[layer].contains(bit))
//		{
//			return m_shared_systems[layer][bit];
//		}
//	}
//	for (int layer = 0; layer < MAX_DRAW_LAYER; ++layer)
//	{
//		if (m_shared_render_systems[layer].contains(bit))
//		{
//			return m_shared_render_systems[layer][bit];
//		}
//	}
//	return nullptr;
//}

/**
* @brief 共有システム解放
*/
void SystemManager::ReleaseSharedSystem()
{
	for (auto& system_layer : m_shared_systems)
	{
		for (auto& system : system_layer)
		{
			if (system.second != nullptr)
			{
				delete system.second;
				system.second = nullptr;
			}
		}
	}
	for (auto& system_layer : m_shared_render_systems)
	{
		for (auto& system : system_layer)
		{
			if (system.second != nullptr)
			{
				delete system.second;
				system.second = nullptr;
			}
		}
	}
}

} // namespace HaraProject::Framework