#include <DirectXMath.h>

#include "imgui.h"

#include "ThreadPoolManager.h"
#include "ScreenFade.h"
#include "WorldManager.h"

namespace HaraProject::Framework {

static const float DEFAULT_FADE_OUT_SEC = 0.55f;
static const float DEFAULT_FADE_IN_SEC = 0.55f;

/**
* @brief 全体更新
*/
void WorldManager::Update(float deltaTime)
{
	switch (m_general_state)
	{
	case NomalUpdate:
		UpdateWorlds(deltaTime);
		if (m_world_activate_handle.IsWait())
		{
			// ロード画面を挟むならロード画面のロードと次のワールドのロードを開始
			if (m_world_activate_handle.NeedShowLoadingScreen())
			{
				if (m_loading_screen_world == nullptr)
				{
					// ロード画面用ワールド・呼び出すワールドをロード開始
					m_loading_screen_world = new WorldBase(m_world_activate_handle.GetLoadingWorldName());
					m_loding_next_world = new WorldBase(m_world_activate_handle.GetWorldName());
					// ロード画面用ワールドのロード待ち状態へ変更
					m_general_state = ReadyLoadingScreen;
				}
			}
			else
			{
				if (m_loding_next_world == nullptr)
				{
					// 呼び出すワールドをロード開始
					m_loding_next_world = new WorldBase(m_world_activate_handle.GetWorldName());
				}
				// フェードを使用するなら
				if (m_world_activate_handle.NeedUseFade())
				{
					// フェードアウト開始
					ScreenFade::Instance().FadeOutStart(DEFAULT_FADE_OUT_SEC, DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
					m_general_state = FadeOut;
				}
				// フェードを使用しないなら
				else
				{
					// ロードが終わり次第通常更新状態へ
					if (m_loding_next_world->IsCompleteLoad())
					{
						// ロードしたワールドをアクティブなワールドとして追加
						m_current_worlds.push_back(m_loding_next_world);
						m_loding_next_world = nullptr;

						// ハンドルをリセット
						m_world_activate_handle.Reset();
					}
				}
			}
		}
		break;
	case ReadyLoadingScreen:
		UpdateWorlds(deltaTime);
		// ロード画面用ワールドのロードが完了したら
		if (m_loading_screen_world->IsCompleteLoad())
		{
			// フェードアウト開始
			ScreenFade::Instance().FadeOutStart(DEFAULT_FADE_OUT_SEC, DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
			m_general_state = FadeOut;
		}
		break;
	case Loading:
		m_loading_screen_world->UpdateWorld(deltaTime);
		// 呼び出すワールドのロードが完了したら
		if (m_loding_next_world->IsCompleteLoad())
		{
			// ロードしたワールドをアクティブなワールドとして追加
			m_current_worlds.push_back(m_loding_next_world);
			m_loding_next_world = nullptr;
			// フェードイン開始
			ScreenFade::Instance().FadeInStart(DEFAULT_FADE_IN_SEC);
			m_general_state = FadeIn;
		}
		break;
	case FadeOut:
		if (ScreenFade::Instance().IsFade())
		{
			// フェード中は更新処理のみ行い終了
			UpdateWorlds(deltaTime);
			ScreenFade::Instance().UpdateFade(deltaTime);
			return;
		}
		// 入れ替えモードなら
		if (m_world_activate_handle.GetActivateMode() == WorldActivateHandle::Change)
		{
			// 一番上のワールドを削除
			if (!m_current_worlds.empty())
			{
				ReleaseWorld(m_current_worlds.back()->GetName());
			}
		}

		// ロード画面を挟まない場合
		if (!m_world_activate_handle.NeedShowLoadingScreen())
		{
			// フェードアウトしたままロードを待ち、完了したら
			if (m_loding_next_world->IsCompleteLoad())
			{
				// ロードしたワールドをアクティブなワールドとして追加
				m_current_worlds.push_back(m_loding_next_world);
				m_loding_next_world = nullptr;
				// フェードイン開始
				ScreenFade::Instance().FadeInStart(DEFAULT_FADE_IN_SEC);
				m_general_state = FadeIn;
			}
		}
		// ロード画面を挟む場合
		else
		{
			// 状態をロード中に変更
			m_general_state = Loading;
		}
		break;
	case FadeIn:
		UpdateWorlds(deltaTime);
		if (ScreenFade::Instance().IsFade())
		{
			// フェード中は更新処理のみを行い終了
			ScreenFade::Instance().UpdateFade(deltaTime);
			return;
		}
		// ハンドルをリセット
		m_world_activate_handle.Reset();
		// フェードインが完了したら状態を通常更新に変更
		m_general_state = NomalUpdate;
		break;
	}
}

/**
* @brief 全体描画
*/
void WorldManager::Draw()
{
	switch (m_general_state)
	{
	case NomalUpdate:
		DrawWorlds();
		break;
	case Loading:
		m_loading_screen_world->DrawWorld();
		break;
	case FadeOut:
	case FadeIn:
		DrawWorlds();
		ScreenFade::Instance().DrawFade();
		break;
	}
}

/**
* @brief アクティブなワールドを更新
*/
void WorldManager::UpdateWorlds(float deltaTime)
{
	for (const auto& world : m_current_worlds)
	{
		world->UpdateWorld(deltaTime);
	}
}

/**
* @brief アクティブなワールドを描画
*/
void WorldManager::DrawWorlds()
{
	for (const auto& world : m_current_worlds)
	{
		world->DrawWorld();
	}
}

/**
* @brief 最初のワールドを起動
*/
void WorldManager::ActivateBeginningWorld()
{
	// 最初に呼ぶワールド名を取得
	std::string world_name = m_edit_data_manager.LoadBeginningWorldName();
	// 起動
	ActivateWorld(world_name, WorldActivateHandle::Change, false);
}

/**
* @brief ワールドを解放する
* @param[in] worldTag ワールド名
*/
void WorldManager::ReleaseWorld(std::string worldName)
{
	// 指定のワールドを解放して要素を削除する
	std::erase_if(m_current_worlds, 
		[worldName](WorldBase* world)
		{
			if (world->GetName() == worldName)
			{
				delete world;
				return true;
			}
			return false;
		});
}

/**
* @brief 全ワールドを解放
*/
void WorldManager::ReleaseAllWorlds()
{
	for (auto& world : m_current_worlds)
	{
		if (world != nullptr)
		{
			delete world;
			world = nullptr;
		}
	}
	m_current_worlds.clear();
}

/**
* @brief 次のワールド呼び出し情報を設定
* @param[in] worldName ワールド名
* @param[in] mode 呼び出しモード
*/
void WorldManager::ActivateWorld(std::string worldName, WorldActivateHandle::ActivateMode mode, bool useFade, bool showLoadingScreen, std::string loadingWorldName)
{
	m_world_activate_handle.Set(worldName, mode, useFade, showLoadingScreen, loadingWorldName);
}

/**
* @brief コンストラクタ
*/
WorldManager::WorldManager()
	: m_loading_screen_world(nullptr)
	, m_loding_next_world(nullptr)
	, m_general_state(NomalUpdate)
{
}

/**
* @brief デストラクタ
*/
WorldManager::~WorldManager()
{
	ReleaseAllWorlds();
}

/**
* @brief ワールドを重ねる
* @param[in] worldName ワールド名
*/
void WorldManager::AdditiveWorld(std::string worldName)
{
	m_current_worlds.push_back(new WorldBase(worldName));
}

}// namespace HaraProject::Framework