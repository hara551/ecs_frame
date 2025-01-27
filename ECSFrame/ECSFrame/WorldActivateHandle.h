/**
* @file   WorldActivateHandle.h
* @brief  ワールドの呼び出し情報管理クラス定義.
* @author Hara Sota.
* @date   2024/10/17
*/
#ifndef _WORLD_ACTIVATE_HANDLE_H_
#define _WORLD_ACTIVATE_HANDLE_H_

#include <string>

namespace HaraProject::Framework {

/**
 * @brief ワールドの呼び出し情報を管理するクラス
 */
class WorldActivateHandle
{
public:
    /**
     * @brief ワールドの呼び出しモード
     */
    enum ActivateMode
    {
        Change,   // 現在のワールドを切り替える
        Additive  // 現在のワールドに追加する
    };

    /**
     * @brief コンストラクタ
     */
    WorldActivateHandle();

    /**
     * @brief パラメータを設定
     * @param[in] worldName ワールド名
     * @param[in] mode 切り替えモード
     * @param[in] useFade フェードを使用するか
     * @param[in] showLoadingScreen ローディング画面を表示するか
     * @param[in] loadingWorldName ローディング画面用のワールド名
     */
    void Set(const std::string& worldName, ActivateMode mode, bool useFade, bool showLoadingScreen, const std::string& loadingWorldName = "");

    /**
     * @brief 初期状態にリセット
     */
    void Reset();

    /**
    * @brief 呼び出すワールド名を取得
    */
    std::string GetWorldName() {
        return m_world_name;
    }

    /**
    * @brief 呼び出しモード取得
    */
    ActivateMode GetActivateMode() {
        return m_activate_mode;
    }

    /**
    * @brief フェード使用フラグ取得
    */
    bool NeedUseFade() {
        return m_use_fade;
    }

    /**
    * @brief ロード画面表示フラグ取得
    */
    bool NeedShowLoadingScreen() {
        return m_show_loading_screen;
    }

    /**
    * @brief ロード画面用ワールドの名前を取得
    */
    std::string GetLoadingWorldName() {
        return m_loading_world_name;
    }

    /**
    * @brief 呼び出し待機中か
    */
    bool IsWait() {
        return m_is_wait;
    }

    /**
    * @brief 待機状態を設定
    */
    void SetIsWait(bool isWait) {
        m_is_wait = isWait;
    }

private:
    /**
    * @brief 呼び出すワールドの名前
    */
    std::string m_world_name;

    /**
    * @brief 呼び出しモード
    */
    ActivateMode m_activate_mode;   

    /**
    * @brief フェードを使用するか
    */
    bool m_use_fade;             

    /**
    * @brief ロード画面を表示するか
    */
    bool m_show_loading_screen;    

    /**
    * @brief 表示するロード画面用ワールドの名前
    */
    std::string m_loading_world_name; 

    /**
    * @brief 呼び出し待機中か
    */
    bool m_is_wait;
};

} // namespace HaraProject::Framework

#endif // !_WORLD_ACTIVATE_HANDLE_H_
