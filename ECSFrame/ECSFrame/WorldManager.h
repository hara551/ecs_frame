/**
* @file   WorldManager.h
* @brief  �Q�[���S�̂̊Ǘ��N���X��`.
* @author Hara Sota.
* @date   2024/10/17
*/
#ifndef _WORLD_MANAGER_H_
#define _WORLD_MANAGER_H_

#include <vector>
#include <string>

#include "WorldBase.h"
#include "WorldActivateHandle.h"
#include "EditDataManager.h"

namespace HaraProject::Framework {

/**
* @brief �Q�[���S�̂̊Ǘ��N���X
* @attention �V���O���g��
*/
class WorldManager
{
public:
	/**
	* @brief �Q�[���S�̂̏��
	*/
	enum GeneralState
	{
		NomalUpdate,		// �ʏ�X�V��
		ReadyLoadingScreen, // ���[�h��ʂ̃��[�h��
		Loading,			// ���[�h��
		FadeOut,			// �t�F�[�h�A�E�g��
		FadeIn,				// �t�F�[�h�C����
	};

	/**
	* @brief �R�s�[�R���X�g���N�^�֎~
	*/
	WorldManager(const WorldManager&) = delete;

	/**
	* @brief ����֎~
	*/
	WorldManager& operator=(const WorldManager&) = delete;

	/**
	* @brief �C���X�^���X�擾
	*/
	static WorldManager& Instance()
	{
		static WorldManager _instance;
		return _instance;
	}

	/**
	* @brief �S�̍X�V
	*/
	void Update(float deltaTime);

	/**
	* @brief �S�̕`��
	*/
	void Draw();

	/**
	* @brief �A�N�e�B�u�ȃ��[���h���X�V
	*/
	void UpdateWorlds(float deltaTime);

	/**
	* @brief �A�N�e�B�u�ȃ��[���h��`��
	*/
	void DrawWorlds();

	/**
	* @brief �ŏ��̃��[���h���N��
	*/
	void ActivateBeginningWorld();

	/**
	* @brief ���[���h��L���ɂ���
	* @param[in] worldName ���[���h��
	* @param[in] mode �Ăяo�����[�h
	*/
	void ActivateWorld(std::string worldName, WorldActivateHandle::ActivateMode mode, bool useFade = true, bool showLoadingScreen = false, std::string loadingWorldName = "");

	/**
	* @brief ���[���h�����
	* @param[in] worldTag ���[���h��
	*/
	void ReleaseWorld(std::string worldName);

	/**
	* @brief �S���[���h�����
	*/
	void ReleaseAllWorlds();

private:
	/**
	* @brief �R���X�g���N�^
	*/
	WorldManager();

	/**
	* @brief �f�X�g���N�^
	*/
	~WorldManager();

	/**
	* @brief ���[���h���d�˂�
	* @param[in] worldName ���[���h��
	*/
	void AdditiveWorld(std::string worldName);


	/**
	* @brief ���[���h�ꗗ
	*/
	std::vector<WorldBase*> m_current_worlds;

	/**
	* @brief ���ɌĂяo�����[�h�����[���h
	*/
	WorldBase* m_loding_next_world;

	/**
	* @brief ���[�h��ʐ�p���[���h
	*/
	WorldBase* m_loading_screen_world;

	/**
	* @brief ���[���h�Ăяo�����
	*/
	WorldActivateHandle m_world_activate_handle;

	/**
	* @brief �ҏW�f�[�^�Ǘ�
	*/
	EditDataManager m_edit_data_manager;

	/**
	* @brief �Q�[���S�̂̏��
	*/
	GeneralState m_general_state;
};
}// namespace HaraProject::Framework


#endif // _WORLD_MANAGER_H_