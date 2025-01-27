/**
* @file   WorldWindow.h
* @brief  ワールド情報ウィンドウ.
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
* @brief ワールドウィンドウプロパティ
*/
static const char* WORLD_WINDOW_TITLE = "World";
static const float WORLD_WINDOW_SIZE_X = 300.0f;
static const float WORLD_WINDOW_SIZE_Y = 720.0f;
static const float WORLD_WINDOW_POS_X = 0.0f;
static const float WORLD_WINDOW_POS_Y = 0.0f;

/**
* @breif ワールドメニュープロパティ
*/
static const char* WORLD_MENU_TITLE = "WorldMenu";

/**
* @breif サブシーンメニュープロパティ
*/
static const char* SUBSCENE_MENU_TITLE = "SubSceneMenu";

class WorldWindow : public WindowBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	WorldWindow(EditorManager* editorManager);

	/**
	* @brief 更新処理
	*/
	void UpdateWindow()override;

	/**
	* @brief ワールドメニュー
	*/
	void CreateWorldMenu();

	/**
	* @brief サブシーンメニュー
	*/
	void CreateSubSceneMenu();

	/**
	* @brief テキスト入力ダイアログを開く
	* @param[in] inputMode 入力モード
	*/
	void OpenTextInputDialog(TextInputDialog::InputMode inputMode);

	/**
	* @brief 詳細表示を更新する
	* @param[in] detailTargetType 詳細表示ターゲットの種類
	*/
	void UpdateDetail(DetailsWindow::DetailTargetType detailTargetType);
};

}// !namespace HaraProject::Framework {


#endif // !_WORLD_WINDOW_H_
