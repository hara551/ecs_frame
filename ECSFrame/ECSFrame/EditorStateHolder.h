/**
* @file   EditorStateHolder.h
* @brief  �G�f�B�^�[�̏�Ԃ��ꌳ�Ǘ�.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _EDITOR_STATE_HOLDER_H_
#define _EDITOR_STATE_HOLDER_H_

#include <cstdint>
#include <string>

namespace HaraProject::Framework {

class EditorStateHolder
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
	EditorStateHolder()
		: m_edit_mode(EditMode::Edit)
		, m_select_entity_id(0)
		, m_select_subscene_name("")
		, m_edit_world_name("SubScene_Transform")
	{};

	/**
	* @brief �f�X�g���N�^
	*/
	~EditorStateHolder() = default;

	/**
	* @brief ���݂̕ҏW���[�h���擾
	*/
	EditMode GetEditMode() {
		return m_edit_mode;
	}

	/**
	* @brief �I�𒆂̃G���e�B�e�BID���擾
	*/
	uint32_t GetSelectEntityId() {
		return m_select_entity_id;
	}

	/**
	* @brief �I�𒆂̃T�u�V�[�������擾
	*/
	std::string GetSelectSubSceneName() {
		return m_select_subscene_name;
	}

	/**
	* @brief �ҏW���̃��[���h�����擾
	*/
	std::string GetEditWorldName() {
		return m_edit_world_name;
	}

	/**
	* @brief �ҏW���[�h��ݒ�
	*/
	void SetEditMode(EditMode editMode) {
		m_edit_mode = editMode;
	}

	/**
	* @brief �I�𒆂̃T�u�V�[������ݒ�
	* @param[in] subsceneName �T�u�V�[����
	*/
	void SetSelectSubSceneName(std::string subsceneName) {
		m_select_subscene_name = subsceneName;
	}

	/**
	* @brief �I�𒆂̃G���e�B�e�BID��ݒ�
	* @param[in] id �G���e�B�e�BID
	*/
	void SetSelectEntityId(uint32_t id) {
		m_select_entity_id = id;
	}

	/**
	* @brief �ҏW���̃��[���h����ݒ�
	* @param[in] worldName ���[���h��
	*/
	void SetEditWorldName(std::string worldName) {
		m_edit_world_name = worldName;
	}

private:
	/**
	* @brief ���݂̕ҏW���[�h
	*/
	EditMode m_edit_mode;

	/**
	* @brief �I�𒆂̃G���e�B�e�BID
	*/
	uint32_t m_select_entity_id;

	/**
	* @brief �I�𒆂̃T�u�V�[����
	*/
	std::string m_select_subscene_name;

	/**
	* @brief �ҏW���̃��[���h��
	*/
	std::string m_edit_world_name;
};

}// !namespace HaraProject::Framework

#endif // !_EDITOR_STATE_HOLDER_H_
