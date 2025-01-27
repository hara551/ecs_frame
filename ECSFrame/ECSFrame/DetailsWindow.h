/**
* @file   DetailsWindow.h
* @brief  �ڍ׃E�B���h�E�Ǘ�.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _DETAILS_WINDOW_H_
#define _DETAILS_WINDOW_H_

#include "WindowBase.h"

namespace HaraProject::Framework {

class EditorManager;

static const char* DETAILS_WINDOW_TITLE = "Details";
static const float DETAILS_WINDOW_SIZE_X = 300.0f;
static const float DETAILS_WINDOW_SIZE_Y = 720;
static const float DETAILS_WINDOW_POS_X = 1280 - DETAILS_WINDOW_SIZE_X;
static const float DETAILS_WINDOW_POS_Y = 0.0f;

class DetailsWindow : public WindowBase
{
public:
	/**
	* @brief �ڍו\���^�[�Q�b�g�̎��
	*/
	enum DetailTargetType
	{
		DetailTargetType_Entity,
		DetailTragetType_SubScene,
		DetailTargetType_World,
	};

	/**
	* @brief �R���X�g���N�^
	*/
	DetailsWindow(EditorManager* editorManager);

	/**
	* @brief �X�V����
	*/
	void UpdateWindow()override;

	/**
	* @brief �ڍו\������^�[�Q�b�g�̎�ނ�ݒ�
	* @param[in] detailTargetType �ڍו\���^�[�Q�b�g�̎��
	*/
	void SetDetailTargetType(DetailTargetType detailTargetType);

	/**
	* @brief �ڍו\���̎�ނ��w�肵�čX�V����
	* @param[in] detailTargetType �ڍו\���^�[�Q�b�g�̎��
	*/
	void ChangeDetailContent(DetailTargetType detailTargetType);
	
private:
	/**
	* @brief �ڍו\������^�[�Q�b�g�̎��
	*/
	DetailTargetType m_detail_target_type;
};

}// !namespace HaraProject::Framework {


#endif // !_DETAILS_WINDOW_H_
