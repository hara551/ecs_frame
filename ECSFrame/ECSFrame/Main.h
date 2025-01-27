/**
* @file   Main.h
* @brief  メインループ定義.
* @author Hara Sota.
* @date   //
*/
#ifndef __MAIN_H__
#define __MAIN_H__

#include <Windows.h>

namespace HaraProject::Framework {

/**
* @brief 初期化処理
*/
HRESULT Init(HWND hWnd, UINT width, UINT height);

/**
* @brief 終了処理
*/
void Uninit();				

/**
* @brief 更新処理
*/
void Update(float deltaTime);

/**
* @brief 描画処理
*/
void Draw();				

}// !namespace HaraProject::Framework 

#endif // __MAIN_H__