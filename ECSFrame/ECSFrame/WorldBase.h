/**
* @file   WorldBase.h
* @brief  ECS�Ǘ��P�ʃN���X��`.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _WORLD_BASE_H_
#define _WORLD_BASE_H_

#include <string>
#include <mutex>

#include "ComponentDataManager.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "IEditDataLoader.h"

namespace HaraProject::Framework {

class WorldBase
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param[in] worldName ���[���h��
	*/
	WorldBase(std::string worldName);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~WorldBase();

	/**
	* @brief ���[���h�X�V����
	*/
	void UpdateWorld(float deltaTime);

	/**
	* @brief ���[���h�`�揈��
	*/
	void DrawWorld();

	/**
	* @brief ���[�h�������������m�F
	*/
	bool IsCompleteLoad();

	/**
	* @brief ���[���h���擾
	*/
	std::string GetName();

	/**
	* @brief �G���e�B�e�B�}�l�[�W���[�擾
	*/
	EntityManager* GetEntityManager() {
		return m_entity_manager;
	}

	/**
	* @brief �R���|�[�l���g�f�[�^�}�l�[�W���[�擾
	*/
	ComponentDataManager* GetComponentDataManager() {
		return m_component_data_manager;
	}

	/**
	* @brief �V�X�e���}�l�[�W���[�擾
	*/
	SystemManager* GetSystemManager() {
		return m_system_manager;
	}

protected:
	/**
	* @brief ���[���h����������
	*/
	virtual void InitWorld();

	/**
	* @brief ���[���h�I������
	*/
	virtual void UninitWorld();

	/**
	* @brief ����̃V�X�e����o�^
	*/
	void RegisterWorldSystems();

	/**
	* @brief ���[���h�̃G���e�B�e�B��S�č쐬
	*/
	void CreateEntities();

	/**
	* @brief ���[���h�ɕK�v�ȃ��\�[�X�����[�h
	*/
	void LoadWorldResources();

	/**
	* @brief ���\�[�X��K�v�ȃG���e�B�e�B�ɃZ�b�g����
	*/
	void SettingResourcesToEntity();

	/**
	* @brief ���[���h��
	*/
	std::string m_world_name;

	/**
	* @brief ���[�h���̃��\�[�X��
	*/
	int32_t m_num_resource_loading;

	/**
	* @brief ���[�h�i���m�F�񍐗p���b�N
	*/
	std::mutex m_loaded_sign_mutex;

	/**
	* @brief �R���|�[�l���g�f�[�^�Ǘ�
	*/
	ComponentDataManager* m_component_data_manager;

	/**
	* @brief �G���e�B�e�B�Ǘ�
	*/
	EntityManager* m_entity_manager;

	/**
	* @brief �V�X�e���Ǘ�
	*/
	SystemManager* m_system_manager;

	/**
	* @brief �ҏW�f�[�^�̓ǂݍ��݃C���^�t�F�[�X
	*/
	IEditDataLoader* m_edit_data_loder;
};

} // !namespace HaraProject::Framework

#endif // !_WORLD_BASE_H_
