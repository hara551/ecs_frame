/**
* @file   ClipboardHolder.h
* @brief  �G�f�B�^�[�̃R�s�y�@�\�Ǘ�.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _CLIP_BOARD_HOLDER_H_
#define _CLIP_BOARD_HOLDER_H_

#include <string>
#include <unordered_map>

#include "ComponentMask.h"
#include "ComponentDataBase.h"

namespace HaraProject::Framework {

class ClipboardHolder
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	ClipboardHolder() = default;

	/**
	* @brief �f�X�g���N�^
	*/
	~ClipboardHolder() = default;

	/**
	* @brief �R�s�[���ꂽ�G���e�B�e�B�f�[�^���擾
	*/
	std::unordered_map<ComponentBits, ComponentDataBase*> GetCopyEntityData() {
		return m_copy_entity_data;
	}

	/**
	* @brief �R�s�[�p�G���e�B�e�B�f�[�^��ݒ�
	* @param[in] copyEntityData �R�s�[�����G���e�B�e�B�f�[�^
	*/
	void SetCopyEntityData(std::unordered_map<ComponentBits, ComponentDataBase*> copyEntityData) {
		m_copy_entity_data = copyEntityData;
	}

private:
	/**
	* @brief �R�s�[�����G���e�B�e�B�f�[�^
	*/
	std::unordered_map<ComponentBits, ComponentDataBase*> m_copy_entity_data;


};

}// !namespace HaraProject::Framework

#endif // !_CLIP_BOARD_HOLDER_H_