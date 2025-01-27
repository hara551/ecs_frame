#include <string>
#include <vector>

#include "Main.h"
#include "DirectX.h"
#include "SpriteRenderer.h"
#include "Geometory.h"
#include "Input.h"
#include "SoundManager.h"
#include "ComponentDataBase.h"
#include "ComponentRegistry.h"
#include "EditorManager.h"
#include "WorldManager.h"
#include "WorldActivateHandle.h"

namespace HaraProject::Framework {
#ifdef _DEBUG
EditorManager* g_editor_manager;
#endif // _DEBUG

/**
* @brief ‰Šú‰»ˆ—
*/
HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr = HRESULT{};

	InitDirectX(hWnd, width, height, false);

	InitInput();
	SoundManager::Instance().InitSound();

	Geometory::Init();
	HAL::SasakiRyota::SpriteRenderer::Init();

	ComponentRegistry::RegisterAllComponentData();

#ifdef _DEBUG

	g_editor_manager = new EditorManager();

#else

	WorldManager::Instance().ActivateBeginningWorld();

#endif // _DEBUG

	return hr;
}

/**
* @brief I—¹ˆ—
*/
void Uninit()
{
	WorldManager::Instance().ReleaseAllWorlds();

#ifdef _DEBUG

	delete g_editor_manager;

#endif // _DEBUG

	HAL::SasakiRyota::SpriteRenderer::Uninit();
	Geometory::Uninit();

	SoundManager::Instance().UninitSound();
	
	UninitInput();

	UninitDirectX();
}

/**
* @brief XVˆ—
*/
void Update(float deltaTime)
{
	UpdateInput();

#ifdef _DEBUG

	if (g_editor_manager->GetEditMode() == EditorManager::Play)
	{
		WorldManager::Instance().Update(deltaTime);
	}

	g_editor_manager->UpdateEditor(deltaTime);
#else

	WorldManager::Instance().Update(deltaTime);

#endif // !_DEBUG
}

/**
* @brief •`‰æˆ—
*/
void Draw()
{
	BeginDrawDirectX();

#ifdef _DEBUG

	if (g_editor_manager->GetEditMode() == EditorManager::Play)
	{
		WorldManager::Instance().Draw();
	}

	g_editor_manager->DrawEditor();

#else

	WorldManager::Instance().Draw();

#endif // !_DEBUG

	EndDrawDirectX();
}

} // ! namespace HaraProject::Framework