/**
* @file   Main.h
* @brief  ���C�����[�v��`.
* @author Hara Sota.
* @date   //
*/
#ifndef __MAIN_H__
#define __MAIN_H__

#include <Windows.h>

namespace HaraProject::Framework {

/**
* @brief ����������
*/
HRESULT Init(HWND hWnd, UINT width, UINT height);

/**
* @brief �I������
*/
void Uninit();				

/**
* @brief �X�V����
*/
void Update(float deltaTime);

/**
* @brief �`�揈��
*/
void Draw();				

}// !namespace HaraProject::Framework 

#endif // __MAIN_H__