/**
* @file   DetailsWindow.h
* @brief  詳細ウィンドウ管理.
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
	* @brief 詳細表示ターゲットの種類
	*/
	enum DetailTargetType
	{
		DetailTargetType_Entity,
		DetailTragetType_SubScene,
		DetailTargetType_World,
	};

	/**
	* @brief コンストラクタ
	*/
	DetailsWindow(EditorManager* editorManager);

	/**
	* @brief 更新処理
	*/
	void UpdateWindow()override;

	/**
	* @brief 詳細表示するターゲットの種類を設定
	* @param[in] detailTargetType 詳細表示ターゲットの種類
	*/
	void SetDetailTargetType(DetailTargetType detailTargetType);

	/**
	* @brief 詳細表示の種類を指定して更新する
	* @param[in] detailTargetType 詳細表示ターゲットの種類
	*/
	void ChangeDetailContent(DetailTargetType detailTargetType);
	
private:
	/**
	* @brief 詳細表示するターゲットの種類
	*/
	DetailTargetType m_detail_target_type;
};

}// !namespace HaraProject::Framework {


#endif // !_DETAILS_WINDOW_H_
