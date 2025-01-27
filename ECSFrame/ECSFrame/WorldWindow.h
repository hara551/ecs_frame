/**
* @file   WorldWindow.h
* @brief  ���[���h���E�B���h�E.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _WORLD_WINDOW_H_
#define _WORLD_WINDOW_H_

#include "WindowBase.h"
#include "TextInputDialog.h"
#include "DetailsWindow.h"

namespace HaraProject::Framework {

class EditorManager;

/**
* @brief ���[���h�E�B���h�E�v���p�e�B
*/
static const char* WORLD_WINDOW_TITLE = "World";
static const float WORLD_WINDOW_SIZE_X = 300.0f;
static const float WORLD_WINDOW_SIZE_Y = 720.0f;
static const float WORLD_WINDOW_POS_X = 0.0f;
static const float WORLD_WINDOW_POS_Y = 0.0f;

/**
* @breif ���[���h���j���[�v���p�e�B
*/
static const char* WORLD_MENU_TITLE = "WorldMenu";

/**
* @breif �T�u�V�[�����j���[�v���p�e�B
*/
static const char* SUBSCENE_MENU_TITLE = "SubSceneMenu";

class WorldWindow : public WindowBase
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	WorldWindow(EditorManager* editorManager);

	/**
	* @brief �X�V����
	*/
	void UpdateWindow()override;

	/**
	* @brief ���[���h���j���[
	*/
	void CreateWorldMenu();

	/**
	* @brief �T�u�V�[�����j���[
	*/
	void CreateSubSceneMenu();

	/**
	* @brief �e�L�X�g���̓_�C�A���O���J��
	* @param[in] inputMode ���̓��[�h
	*/
	void OpenTextInputDialog(TextInputDialog::InputMode inputMode);

	/**
	* @brief �ڍו\�����X�V����
	* @param[in] detailTargetType �ڍו\���^�[�Q�b�g�̎��
	*/
	void UpdateDetail(DetailsWindow::DetailTargetType detailTargetType);
};

}// !namespace HaraProject::Framework {


#endif // !_WORLD_WINDOW_H_
