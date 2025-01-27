/**
* @file   SystemManager.h
* @brief  システム管理クラス定義.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _SYSTEM_MANAGER_H_
#define _SYSTEM_MANAGER_H_

#include <memory>
#include <vector>
#include <string>

#include "nlohmann/json.hpp"

//#include "SystemBase.h"
#include "ISystemDistributor.h"
#include "IChunkProvider.h"
#include "IEntityOperator.h"
#include "SystemMask.h"

namespace HaraProject::Framework {

class SystemBase;
#ifdef _DEBUG
/**
* @brief システム登録情報をJsonに格納するときのキー
*/
//static const char* SYSTEM_NAME_JSON_KEY = "SystemName";
//static const char* RENDER_FLAG_JSON_KEY = "IsRender";
//static const char* SHARE_FLAG_JSON_KEY = "IsShare";
//static const char* LAYER_NUM_JSON_KEY = "Layer";
#endif // _DEBUG

class SystemManager : public ISystemDistributor
{
public:
	/**
	* @brief 処理の種類(更新順決定用)
	* @attention 値が小さいほど優先度が高い
	*/
	enum UpdateProcessType
	{
		UpdateProcessType_Physics,
		UpdateProcessType_None,
		MAX_PROCESS_TYPE
	};

	/**
	* @brief 描画レイヤー
	* @attention 値が小さいほど優先度が高い
	*/
	enum DrawLayer
	{
		UIFront,
		UI,
		Object,
		MAX_DRAW_LAYER
	};

	///**
	//* @brief システムの登録オプションを保持するハンドル
	//*/
	//struct SystemHandle
	//{
	//	/**
	//	* @brief システム識別ビット
	//	*/
	//	SystemBits bit;

	//	/**
	//	* @brief 描画システムか
	//	*/
	//	bool isRenderSystem;

	//	/**
	//	* @brief 他システムと共有するか
	//	*/
	//	bool isShare;

	//	/**
	//	* @brief レイヤー
	//	*/
	//	uint8_t layer;
	//};

	/**
	* @brief コンストラクタ
	* @param[in] entityOperator エンティティ操作用
	* @param[in] chunkProvider チャンク取得用
	*/
	SystemManager(IEntityOperator* entityOperator, IChunkProvider* chunkProvider);

	/**
	* @brief デストラクタ
	*/
	~SystemManager();

	/**
	* @brief システム更新
	*/
	void UpdataSystems(float deltaTime);

	/**
	* @brief 描画システム更新
	*/
	void UpdateRenderSystems();

	/**
	* @brief システム登録
	* @param[in] processType 処理の種類
	* @param[in] isShare 他システムと共有するか
	* @param[in] name システム名
	*/
	template<typename T> void AddSystem(UpdateProcessType processType, bool isShare, std::string name);

	/**
	* @brief 描画システム登録
	* @param[in] layer 描画レイヤー
	* @param[in] isShare 他システムと共有するか
	* @param[in] name システム名
	*/
	template<typename T> void AddRenderSystem(DrawLayer layer, bool isShare, std::string name);

	/**
	* @brief システム取得
	* @param[in] bit システム名
	*/
	SystemBase* FindSystem(std::string name)override;

	///**
	//* @brife システム登録
	//* @param[in] systemHandle システム登録ハンドル
	//*/
	//void AddSystem(SystemHandle systemHandle);

	///**
	//* @brief システム取得
	//* @param[in] bit システム識別ビット
	//*/
	//SystemBase* FindSystem(SystemBits bit)override;

#ifdef _DEBUG
	//nlohmann::json ConvertSystemListToJson()
	//{
	//	nlohmann::json system_list_json;
	//	for (int layer = 0; layer < MAX_PROCESS_TYPE; ++layer)
	//	{
	//		for (const auto& system : m_systems[layer])
	//		{
	//			system_list_json.push_back(system->WriteDataToJson());
	//		}
	//	}
	//	return system_list_json;
	//}
	//nlohmann::json ConvertShareSystemListToJson()
	//{
	//	nlohmann::json system_list_json;
	//	for (int layer = 0; layer < MAX_PROCESS_TYPE; ++layer)
	//	{
	//		for (const auto& system : m_shared_systems[layer])
	//		{
	//			system_list_json.push_back(system.second->WriteDataToJson());
	//		}
	//	}
	//	return system_list_json;
	//}
	//nlohmann::json ConvertRenderSystemListToJson()
	//{
	//	nlohmann::json system_list_json;
	//	for (int layer = 0; layer < MAX_DRAW_LAYER; ++layer)
	//	{
	//		for (const auto& system : m_render_systems[layer])
	//		{
	//			system_list_json.push_back(system->WriteDataToJson());
	//		}
	//	}
	//}
	//nlohmann::json ConvertShareRenderSystemListToJson()
	//{
	//	nlohmann::json system_list_json;
	//	for (int layer = 0; layer < MAX_DRAW_LAYER; ++layer)
	//	{
	//		for (const auto& system : m_shared_render_systems[layer])
	//		{
	//			system_list_json.push_back(system.second->WriteDataToJson());
	//		}
	//	}
	//}
#endif // _DEBUG


private:
	/**
	* @brief 共有システム解放
	*/
	void ReleaseSharedSystem();

	/**
	* @brief レイヤーごとの通常のシステム
	*/
	std::vector<std::vector<std::unique_ptr<SystemBase>>> m_systems;

	/**
	* @brief 他システムでも利用するシステム
	*/
	std::vector<std::unordered_map<std::string, SystemBase*>> m_shared_systems;

	/**
	* @brief レイヤーごとの描画システム
	*/
	std::vector<std::vector<std::unique_ptr<SystemBase>>> m_render_systems;

	/**
	* @brief 他システムでも利用する描画システム
	*/
	std::vector<std::unordered_map<std::string, SystemBase*>> m_shared_render_systems;

	/**
	* @brief エンティティ操作用
	*/
	IEntityOperator* m_entity_operator;

	/**
	* @brief チャンク取得用
	*/
	IChunkProvider* m_chunk_provider;
};

/**
* @brief システム登録
* @param[in] processType 処理の種類
* @param[in] isShare 他システムと共有するか
* @param[in] name システム名
*/
template<typename T>
inline void SystemManager::AddSystem(UpdateProcessType processType, bool isShare, std::string name)
{
	if (isShare)
	{
		if (!m_shared_systems[processType].contains(name))
		{
			m_shared_systems[processType][name] = new T(m_entity_operator, this, m_chunk_provider);
		}
	}
	else
	{
		m_systems[processType].push_back(std::make_unique<T>(m_entity_operator, this, m_chunk_provider));
	}
}

/**
* @brief 描画システム登録
* @param[in] layer 描画レイヤー
* @param[in] isShare 他システムと共有するか
* @param[in] name システム名
*/
template<typename T>
inline void SystemManager::AddRenderSystem(DrawLayer layer, bool isShare, std::string name)
{
	if (isShare)
	{
		if (!m_shared_render_systems[layer].contains(name))
		{
			m_shared_render_systems[layer][name] = new T(m_entity_operator, this, m_chunk_provider);
		}

	}
	else
	{
		m_render_systems[layer].push_back(std::make_unique<T>(m_entity_operator, this, m_chunk_provider));
	}
}

} // namespace HaraProject::Framework

#endif // !_SYSTEM_MANAGER_H_
