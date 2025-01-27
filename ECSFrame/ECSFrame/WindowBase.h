/**
* @file   WindowBase.h
* @brief  �E�B���h�E���N���X.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _WINDOW_BASE_H_
#define _WINDOW_BASE_H_

#include "GuiWindow.h"

namespace HaraProject::Framework {

class EditorManager;

class WindowBase
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	WindowBase(EditorManager* editorManager);
		
	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~WindowBase() = default;

	/**
	* @brief �X�V����
	*/
	virtual void UpdateWindow() { m_need_update = false; };

	/**
	* @brief �X�V���K�v��
	*/
	bool NeedUpdate() { return m_need_update; }

	/**
	* @brief �X�V�t���O��ݒ�
	* @param[in] needUpdate �X�V�t���O
	*/
	void SetNeedUpdate(bool needUpdate) { m_need_update = needUpdate; }

	/**
	* @brief �E�B���h�E�폜
	*/
	void DeleteWindow();

	/**
	* @brief �E�B���h�E�\���ݒ�
	*/
	void SetShow(bool isShow) { m_window->SetShow(isShow); }

	/**
	* @brief �폜���邩
	*/
	bool IsDlelete() { return m_is_delete; }

	/**
	* @brief �폜�t���O�ݒ�
	* @param[in] isDelete �폜�t���O
	*/
	void SetIsDelete(bool isDelete) { m_is_delete = isDelete; }

protected:
	/**
	* @brief �G�f�B�^�[�S�̊Ǘ�
	*/
	EditorManager* m_editor_manager;

	/**
	* @brief �E�B���h�E�A�C�e��
	*/
	GuiWindow* m_window;

	/**
	* @brief �X�V�t���O
	*/
	bool m_need_update;

	/**
	* @brief �폜�t���O
	*/
	bool m_is_delete;
};

}// !namespace HaraProject::Framework {


#endif // !_WINDOW_BASE_H_
