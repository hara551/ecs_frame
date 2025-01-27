/**
* @file   WorldManager.h
* @brief  ゲーム全体の管理クラス定義.
* @author Hara Sota.
* @date   2024/10/17
*/
#ifndef _WORLD_MANAGER_H_
#define _WORLD_MANAGER_H_

#include <vector>
#include <string>

#include "WorldBase.h"
#include "WorldActivateHandle.h"
#include "EditDataManager.h"

namespace HaraProject::Framework {

/**
* @brief ゲーム全体の管理クラス
* @attention シングルトン
*/
class WorldManager
{
public:
	/**
	* @brief ゲーム全体の状態
	*/
	enum GeneralState
	{
		NomalUpdate,		// 通常更新時
		ReadyLoadingScreen, // ロード画面のロード中
		Loading,			// ロード中
		FadeOut,			// フェードアウト中
		FadeIn,				// フェードイン中
	};

	/**
	* @brief コピーコンストラクタ禁止
	*/
	WorldManager(const WorldManager&) = delete;

	/**
	* @brief 代入禁止
	*/
	WorldManager& operator=(const WorldManager&) = delete;

	/**
	* @brief インスタンス取得
	*/
	static WorldManager& Instance()
	{
		static WorldManager _instance;
		return _instance;
	}

	/**
	* @brief 全体更新
	*/
	void Update(float deltaTime);

	/**
	* @brief 全体描画
	*/
	void Draw();

	/**
	* @brief アクティブなワールドを更新
	*/
	void UpdateWorlds(float deltaTime);

	/**
	* @brief アクティブなワールドを描画
	*/
	void DrawWorlds();

	/**
	* @brief 最初のワールドを起動
	*/
	void ActivateBeginningWorld();

	/**
	* @brief ワールドを有効にする
	* @param[in] worldName ワールド名
	* @param[in] mode 呼び出しモード
	*/
	void ActivateWorld(std::string worldName, WorldActivateHandle::ActivateMode mode, bool useFade = true, bool showLoadingScreen = false, std::string loadingWorldName = "");

	/**
	* @brief ワールドを解放
	* @param[in] worldTag ワールド名
	*/
	void ReleaseWorld(std::string worldName);

	/**
	* @brief 全ワールドを解放
	*/
	void ReleaseAllWorlds();

private:
	/**
	* @brief コンストラクタ
	*/
	WorldManager();

	/**
	* @brief デストラクタ
	*/
	~WorldManager();

	/**
	* @brief ワールドを重ねる
	* @param[in] worldName ワールド名
	*/
	void AdditiveWorld(std::string worldName);


	/**
	* @brief ワールド一覧
	*/
	std::vector<WorldBase*> m_current_worlds;

	/**
	* @brief 次に呼び出すロード中ワールド
	*/
	WorldBase* m_loding_next_world;

	/**
	* @brief ロード画面専用ワールド
	*/
	WorldBase* m_loading_screen_world;

	/**
	* @brief ワールド呼び出し情報
	*/
	WorldActivateHandle m_world_activate_handle;

	/**
	* @brief 編集データ管理
	*/
	EditDataManager m_edit_data_manager;

	/**
	* @brief ゲーム全体の状態
	*/
	GeneralState m_general_state;
};
}// namespace HaraProject::Framework


#endif // _WORLD_MANAGER_H_