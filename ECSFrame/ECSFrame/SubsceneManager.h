/**
* @file   SubSceneManager.h
* @brief  �T�u�V�[���Ǘ�.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifdef _DEBUG
#ifndef _SUBSCENE_MANAGER_H_
#define _SUBSCENE_MANAGER_H_

#include <string>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "Transform.h"

namespace HaraProject::Framework {

class EditorManager;

class SubsceneManager
{
public:
	/**
	* @brief �T�u�V�[���ɕR�Â����
	*/
	struct SubsceneData
	{
		/**
		* @brief �g�����X�t�H�[��
		*/
		Transform transform;

		/**
		* @brief �������Ă���G���e�B�e�BID
		*/
		std::vector<uint32_t> entities;
	};

	/**
	* @brief �R���X�g���N�^
	* @param[in] editorManager �G�f�B�^�[�}�l�[�W���[
	*/
	SubsceneManager(EditorManager* editorManager);

	/**
	* @brief �f�X�g���N�^
	*/
	~SubsceneManager() = default;

	/**
	* @brief �V�����T�u�V�[����ǉ�
	* @param[in] subsceneName �T�u�V�[����
	* @param[in] transform �g�����X�t�H�[��
	* @param[in] entities �������Ă���G���e�B�e�BID
	*/
	void AddSubscene(std::string subsceneName, Transform transform = Transform(),
		std::vector<uint32_t> entities = std::vector<uint32_t>());

	/**
	* @brief �T�u�V�[���ɃG���e�B�e�B��ǉ�
	* @param[in] subsceneName �T�u�V�[����
	* @param[in] entityId �G���e�B�e�BID
	*/
	void AddEntityToSubscene(std::string subsceneName, uint32_t entityId);

	/**
	* @brief �T�u�V�[�����폜
	* @param[in] subsceneName �T�u�V�[����
	*/
	void DeleteSubscene(std::string subsceneName);

	/**
	* @brief �T�u�V�[������ύX
	* @param[in] subsceneName �ύX�������T�u�V�[���̖��O
	* @param[in] newName �V�������O
	*/
	void RenameSubscene(std::string subsceneName, std::string newName);

	/**
	* @brief �T�u�V�[���S�̂̈ړ����X�V
	*/
	void UpdateSubScenesTransform();

	/**
	* @brief �T�u�V�[������G���e�B�e�B���폜
	* @param[in] entityId �G���e�B�e�BID
	*/
	void RemoveEntityFromSubscene(uint32_t entityId);

	/**
	* @brief �ێ����Ă���T�u�V�[����S�Ĕp��
	*/
	void CleanUpSubscenes();

	/**
	* @brief �T�u�V�[���̃g�����X�t�H�[�����Q�ƂŎ擾
	* @param[in] subsceneName �T�u�V�[����
	*/
	Transform& GetSubscenesTransform(std::string subsceneName);

	/**
	* @brief �T�u�V�[�����Ƃ̃G���e�B�e�B���擾
	*/
	std::unordered_map<std::string, std::vector<uint32_t>> GetEntitiesBySubscene();

	/**
	* @brief �T�u�V�[���f�[�^���擾
	*/
	std::unordered_map<std::string, SubsceneData> GetSubsceneDatas() {
		return m_name_to_subsceneData;
	}

private:
	/**
	* @brief ���Ȃ��T�u�V�[�����ɕϊ�
	* @param[in] subsceneName �T�u�V�[����
	*/
	std::string ConvertToUniqueSubsceneName(std::string subsceneName);

	/**
	* @brief �T�u�V�[���f�[�^
	*/
	std::unordered_map<std::string, SubsceneData> m_name_to_subsceneData;

	/**
	* @brief �T�u�V�[�����Ƃ̑O�t���[���̃g�����X�t�H�[��
	*/
	std::unordered_map<std::string, Transform> m_name_to_old_transform;

	/**
	* @brief �G�f�B�^�[�S�̊Ǘ�
	*/
	EditorManager* m_editor_manager;
};

}// !namespace HaraProject::Framework

#endif // !_SUBSCENE_MANAGER_H_
#endif // _DEBUG