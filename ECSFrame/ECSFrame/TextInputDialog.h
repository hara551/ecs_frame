/**
* @file   TextInputDialog.h
* @brief  �e�L�X�g���̓_�C�A���O.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _TEXT_INPUT_DIALOG_H_
#define _TEXT_INPUT_DIALOG_H_

#include "WindowBase.h"
#include "GuiInputText.h"

namespace HaraProject::Framework {

class EditorManager;

/**
* @brief �_�C�A���O�v���p�e�B
*/
static const char* TEXT_INPUT_DIALOG_TITLE = "TextInputDialogTitle";
static const float TEXT_INPUT_DIALOG_SIZE_X = 400.0f;
static const float TEXT_INPUT_DIALOG_SIZE_Y = 300.0f;
static const float TEXT_INPUT_DIALOG_POS_X = 1280.0f / 2.0f - TEXT_INPUT_DIALOG_SIZE_X / 2.0f;
static const float TEXT_INPUT_DIALOG_POS_Y = 720.0f / 2.0f - TEXT_INPUT_DIALOG_SIZE_Y / 2.0f;

static const char* RENAME_WORLD_DIALOG_TITLE = "Rename World";
static const char* RENAME_SUBSCENE_DIALOG_TITLE = "Rename SubScene";
static const char* LOAD_WORLD_DIALOG_TITLE = "Load World";
static const char* LOAD_SUBSCENE_DIALOG_TITLE = "Load SubScene";
static const char* CREATE_WORLD_DIALOG_TITLE = "Create World";
static const char* CREATE_SUBSCENE_DIALOG_TITLE = "Create SubScene";
static const char* ADD_COMPONENT_DATA_DIALOG_TITLE = "Add ComponentData";

class TextInputDialog : public WindowBase
{
public:
	/**
	* @breif ���̓��[�h
	*/
	enum InputMode
	{
		InputMode_None,
		InputMode_RenameWorld,
		InputMode_RenameSubScene,
		InputMode_LoadWorld,
		InputMode_LoadSubScene,
		InputMode_CreateWorld,
		InputMode_CreateSubScene,
		InputMode_AddComponentData,
	};

	/**
	* @brief �R���X�g���N�^
	* @param[in] editorManager �G�f�B�^�[�}�l�[�W���[
	*/
	TextInputDialog(EditorManager* editorManager);

	/**
	* @brief �X�V����
	*/
	void UpdateWindow()override;

	/**
	* @brief ���̓��[�h�ݒ�
	* @param[in] inputMode ���̓��[�h
	*/
	void SetInputMode(InputMode inputMode);

	/**
	* @brief �_�C�A���O���J��
	* @param[in] inputMode ���̓��[�h
	*/
	void OpenTextInputDialog(InputMode inputMode);

	/**
	* @brief �_�C�A���O�����
	*/
	void CloseTextInputDialog();

private:
	/**
	* @brief ���݂̓��̓��[�h
	*/
	InputMode m_input_mode;

	/**
	* @brief �e�L�X�g���̓o�b�t�@
	*/
	char m_text_input_buffer[GuiInputText::MAX_INPUT_TEXT_LENGTH];
};

}// !namespace HaraProject::Framework {


#endif // !_TEXT_INPUT_DIALOG_H_
