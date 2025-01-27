/**
* @file   EditorManager.h
* @brief  �G�f�B�^�[�S�̊Ǘ�.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifdef _DEBUG
#ifndef _EDITOR_MANAGER_H_
#define _EDITOR_MANAGER_H_

#include <memory>
#include <vector>
#include <string>

#include "GuiManager.h"
#include "EntityManager.h"
#include "ComponentDataManager.h"
#include "SystemManager.h"
#include "WindowBase.h"

#include "EditDataManager.h"
#include "SubsceneManager.h"

#include "Transform.h"

namespace HaraProject::Framework {

class EditorManager
{
public:
	/**
	* @brief �ҏW���[�h
	*/
	enum EditMode
	{
		Edit,	// ���[���h��ҏW
		Play	// ���[���h�����s
	};

	/**
	* @brief �R���X�g���N�^
	*/
	EditorManager();

	/**
	* @brief �f�X�g���N�^
	*/
	~EditorManager();

	/**
	* @brief ����������
	*/
	void InitEditor();

	/**
	* @brief �I������
	*/
	void UninitEditor();

	/**
	* @brief �G�f�B�^�[�X�V
	*/
	void UpdateEditor(float deltaTime);

	/**
	* @brief ECS�v�f�����Z�b�g
	*/
	void ResetECS();

	/**
	* @brief �G�f�B�^�[�Ŏg�p����V�X�e����o�^
	*/
	void RegisterEditorSystems();

	/**
	* @brief �G�f�B�^�[�`��
	*/
	void DrawEditor();

	/**
	* @brief �ҏW���[�h��ύX
	* @param[in] editMode �ҏW���[�h
	*/
	void ChangeEditMode(EditMode editMode);

	/**
	* @brief ���[���h�����[�h
	*/
	void LoadWorld();

	/**
	* @brief �G���e�B�e�B�ɑ���Ȃ����\�[�X�����[�h
	*/
	void ReloadResource();

	/**
	* @brief �T�u�V�[�������[�h
	* @param[in] subsceneName �T�u�V�[����
	*/
	void LoadSubscene(std::string name);

	/**
	* @brief �T�u�V�[�����쐬
	* @param[in] subsceneName �T�u�V�[����
	*/
	void CreateSubsceen(std::string subsceneName);

	/**
	* @brief �I�𒆂̃T�u�V�[�����폜
	*/
	void DeleteSelectSubScene();

	/**
	* @brief ���[���h���Z�[�u
	*/
	void SaveWorld();

	/**
	* @brief �T�u�V�[�����Z�[�u
	* @param[in] subSceneName �T�u�V�[����
	*/
	void SaveSubscene(std::string subSceneName);

	/**
	* @brief ��̃G���e�B�e�B���쐬
	*/
	void CreateEmptyEntity();

	/**
	* @brief ���[���h���ύX
	* @param[in] newName �V���[���h��
	*/
	void RenameWorld(std::string newName);

	/**
	* @brief �I�𒆂̃T�u�V�[������ύX
	* @param[in] newName �V�T�u�V�[����
	*/
	void RenameSubScene(std::string newName);

	/**
	* @brief �T�u�V�[���̈ړ����G���e�B�e�B�ɔ��f����
	*/
	void UpdateSubSceneTransforms();

	/**
	* @brief �I�𒆂̃T�u�V�[�����̃G���e�B�e�B��S�ăR�s�[����
	*/
	void CopySubsceneEntities();

	/**
	* @brief �R�s�[���̃T�u�V�[���̃G���e�B�e�B��I�𒆂̃T�u�V�[�����ɍ쐬����
	*/
	void PasteSubsceneEntities();

	/**
	* @brief �I�𒆂̃G���e�B�e�B�̃f�[�^���R�s�[���ĕێ�����
	*/
	void CopySelectEntity();

	/**
	* @brief �R�s�[���̃f�[�^�ŃG���e�B�e�B���쐬
	*/
	void PasteEntity();

	/**
	* @brief �I�𒆂̃G���e�B�e�B���폜
	*/
	void DeleteSelectEntity();

	/**
	* @brief GUI�}�l�[�W���[�擾
	*/
	std::shared_ptr<GuiManager> GetGuiManager();

	/**
	* @brief �I�𒆃T�u�V�[���ݒ�
	* @param[in] name �T�u�V�[����
	*/
	void SetSelectSubScene(std::string name);

	/**
	* @brief �I�𒆃T�u�V�[�����擾
	*/
	std::string GetSelectSubScene();

	/**
	* @brief �I�𒆃G���e�B�e�B�ݒ�
	*/
	void SetSelectEntityId(uint32_t id);

	/**
	* @brief �I�𒆃G���e�B�e�BID�擾
	*/
	uint32_t GetSelectEntityId();

	/**
	* @brief �E�B���h�E�擾
	* @param[in] windowName �E�B���h�E��
	*/
	WindowBase* GetWindow(std::string windowName);

	/**
	* @brief �G���e�B�e�B�}�l�[�W���[�擾
	*/
	EntityManager* GetEntityManager();

	/**
	* @brief �R���|�[�l���g�f�[�^�}�l�[�W���[�擾
	*/
	ComponentDataManager* GetComponentDataManager();

	/**
	* @brief �V�X�e���}�l�[�W���[�擾
	*/
	SystemManager* GetSystemManager();

	/**
	* @brief �ҏW���̃��[���h�����擾
	*/
	std::string GetEditWorldName();

	/**
	* @brief �ҏW���[�h�擾
	*/
	EditMode GetEditMode() {
		return m_edit_mode;
	}

	/**
	* @brief �ҏW���[�h�ݒ�
	* @param[in] editMode �ҏW���[�h
	*/
	void SetEditMode(EditMode editMode) {
		m_edit_mode = editMode;
	}

	/**
	* @brief EditDataManager���擾
	*/
	EditDataManager* GetEditDataManager() {
		return m_edit_data_manager;
	}

	/**
	* @brief SubsceneManager���擾
	*/
	SubsceneManager* GetSubsceneManager() {
		return m_subscene_manager;
	}

private:
	/**
	* @brief �E�B���h�E�o�^
	* @param[in] windowName �E�B���h�E��
	*/
	template <typename T>
	void RegisterWindow(std::string windowName) 
	{
		m_name_to_window[windowName] = new T(this); 
	}

	/**
	* @brief GUI�Ǘ�
	*/
	std::shared_ptr<GuiManager> m_gui_manager;

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
	* @brief �E�B���h�E�ꗗ
	*/
	std::unordered_map<std::string, WindowBase*> m_name_to_window;

	/**
	* @brief �ҏW���̃��[���h��
	*/
	std::string m_edit_world_name;

	/**
	* @brief �I�𒆃T�u�V�[����
	*/
	std::string m_select_subscene_name;

	/**
	* @brief �I�𒆃G���e�B�e�B
	*/
	uint32_t m_select_entity_id;

	/**
	* @brief �ҏW���[�h
	*/
	EditMode m_edit_mode;

	/**
	* @brief �R�s�[�����G���e�B�e�B�f�[�^
	*/
	std::unordered_map<ComponentBits, ComponentDataBase*> m_copy_entity_data;

	/**
	* @brief �R�s�[�����T�u�V�[���̃G���e�B�e�B�f�[�^
	*/
	std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>> m_copy_subscene_data;

	/**
	* @brief Gui��\�����邩
	*/
	bool m_is_draw_gui;


	/**
	* @brief �ҏW�f�[�^�Ǘ�
	*/
	EditDataManager* m_edit_data_manager;

	/**
	* @brief �T�u�V�[���Ǘ�
	*/
	SubsceneManager* m_subscene_manager;
};

}// !namespace HaraProject::Framework

#endif // !_EDITOR_MANAGER_H_
#endif // _DEBUG