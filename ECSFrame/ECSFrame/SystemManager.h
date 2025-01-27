/**
* @file   SystemManager.h
* @brief  �V�X�e���Ǘ��N���X��`.
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
* @brief �V�X�e���o�^����Json�Ɋi�[����Ƃ��̃L�[
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
	* @brief �����̎��(�X�V������p)
	* @attention �l���������قǗD��x������
	*/
	enum UpdateProcessType
	{
		UpdateProcessType_Physics,
		UpdateProcessType_None,
		MAX_PROCESS_TYPE
	};

	/**
	* @brief �`�惌�C���[
	* @attention �l���������قǗD��x������
	*/
	enum DrawLayer
	{
		UIFront,
		UI,
		Object,
		MAX_DRAW_LAYER
	};

	///**
	//* @brief �V�X�e���̓o�^�I�v�V������ێ�����n���h��
	//*/
	//struct SystemHandle
	//{
	//	/**
	//	* @brief �V�X�e�����ʃr�b�g
	//	*/
	//	SystemBits bit;

	//	/**
	//	* @brief �`��V�X�e����
	//	*/
	//	bool isRenderSystem;

	//	/**
	//	* @brief ���V�X�e���Ƌ��L���邩
	//	*/
	//	bool isShare;

	//	/**
	//	* @brief ���C���[
	//	*/
	//	uint8_t layer;
	//};

	/**
	* @brief �R���X�g���N�^
	* @param[in] entityOperator �G���e�B�e�B����p
	* @param[in] chunkProvider �`�����N�擾�p
	*/
	SystemManager(IEntityOperator* entityOperator, IChunkProvider* chunkProvider);

	/**
	* @brief �f�X�g���N�^
	*/
	~SystemManager();

	/**
	* @brief �V�X�e���X�V
	*/
	void UpdataSystems(float deltaTime);

	/**
	* @brief �`��V�X�e���X�V
	*/
	void UpdateRenderSystems();

	/**
	* @brief �V�X�e���o�^
	* @param[in] processType �����̎��
	* @param[in] isShare ���V�X�e���Ƌ��L���邩
	* @param[in] name �V�X�e����
	*/
	template<typename T> void AddSystem(UpdateProcessType processType, bool isShare, std::string name);

	/**
	* @brief �`��V�X�e���o�^
	* @param[in] layer �`�惌�C���[
	* @param[in] isShare ���V�X�e���Ƌ��L���邩
	* @param[in] name �V�X�e����
	*/
	template<typename T> void AddRenderSystem(DrawLayer layer, bool isShare, std::string name);

	/**
	* @brief �V�X�e���擾
	* @param[in] bit �V�X�e����
	*/
	SystemBase* FindSystem(std::string name)override;

	///**
	//* @brife �V�X�e���o�^
	//* @param[in] systemHandle �V�X�e���o�^�n���h��
	//*/
	//void AddSystem(SystemHandle systemHandle);

	///**
	//* @brief �V�X�e���擾
	//* @param[in] bit �V�X�e�����ʃr�b�g
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
	* @brief ���L�V�X�e�����
	*/
	void ReleaseSharedSystem();

	/**
	* @brief ���C���[���Ƃ̒ʏ�̃V�X�e��
	*/
	std::vector<std::vector<std::unique_ptr<SystemBase>>> m_systems;

	/**
	* @brief ���V�X�e���ł����p����V�X�e��
	*/
	std::vector<std::unordered_map<std::string, SystemBase*>> m_shared_systems;

	/**
	* @brief ���C���[���Ƃ̕`��V�X�e��
	*/
	std::vector<std::vector<std::unique_ptr<SystemBase>>> m_render_systems;

	/**
	* @brief ���V�X�e���ł����p����`��V�X�e��
	*/
	std::vector<std::unordered_map<std::string, SystemBase*>> m_shared_render_systems;

	/**
	* @brief �G���e�B�e�B����p
	*/
	IEntityOperator* m_entity_operator;

	/**
	* @brief �`�����N�擾�p
	*/
	IChunkProvider* m_chunk_provider;
};

/**
* @brief �V�X�e���o�^
* @param[in] processType �����̎��
* @param[in] isShare ���V�X�e���Ƌ��L���邩
* @param[in] name �V�X�e����
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
* @brief �`��V�X�e���o�^
* @param[in] layer �`�惌�C���[
* @param[in] isShare ���V�X�e���Ƌ��L���邩
* @param[in] name �V�X�e����
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
