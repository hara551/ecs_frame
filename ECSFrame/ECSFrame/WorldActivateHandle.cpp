
#include <string>
#include "WorldActivateHandle.h"

namespace HaraProject::Framework {

/**
 * @brief コンストラクタ
 */
WorldActivateHandle::WorldActivateHandle()
	: m_activate_mode(Change)
	, m_world_name("")
	, m_use_fade(true)
	, m_show_loading_screen(false)
	, m_loading_world_name("")
	, m_is_wait(false)
{
}

/**
 * @brief パラメータを設定
 * @param[in] worldName ワールド名
 * @param[in] mode 切り替えモード
 * @param[in] useFade フェードを使用するか
 * @param[in] showLoadingScreen ローディング画面を表示するか
 * @param[in] loadingWorldName ローディング画面用のワールド名
 */
void WorldActivateHandle::Set(const std::string& worldName, ActivateMode mode, bool useFade, bool showLoadingScreen, const std::string& loadingWorldName)
{
	m_world_name = worldName;
	m_activate_mode = mode;
	m_use_fade = useFade;
	m_show_loading_screen = showLoadingScreen;
	m_loading_world_name = loadingWorldName;
	m_is_wait = true;
}

/**
 * @brief 初期状態にリセット
 */
void WorldActivateHandle::Reset()
{
	m_world_name = "";
	m_use_fade = true;
	m_show_loading_screen = false;
	m_loading_world_name = "";
	m_is_wait = false;
}

} // namespace HaraProject::Framework