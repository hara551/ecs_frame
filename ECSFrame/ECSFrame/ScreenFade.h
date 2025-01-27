/**
* @file ScreenFade.h
* @brief 画面のフェード処理
* @author HaraSota
* @date 2024/11/09
*/
#ifndef _SCREEN_FADE_H_
#define _SCREEN_FADE_H_

#include <DirectXMath.h>

#include "EasingUtil.h"

namespace HaraProject::Framework {

/**
* @brief 画面フェードクラス
* @attention シングルトン
*/
class ScreenFade 
{
public:
	/**
	* @brief コピーコンストラクタ禁止
	*/
	ScreenFade(const ScreenFade&) = delete;

	/**
	* @brief 代入禁止
	*/
	ScreenFade& operator=(const ScreenFade&) = delete;

	/**
	* @brief インスタンス取得
	*/
	static ScreenFade& Instance()
	{
		static ScreenFade instance;
		return instance;
	}

	/**
	* @brief フェード更新
	*/
	void UpdateFade(float deltaTime);

	/**
	* @brief フェード描画
	*/
	void DrawFade();

	/**
	* @brief フェードアウト開始
	* @param[in] durationSec かける秒数
	* @param[in] rgb 完了時の色
	* @param[in] easeType 補間タイプ
	*/
	void FadeOutStart(float durationSec, DirectX::XMFLOAT3 rgb, EaseType easeType = EaseType::Linear, EaseDir easeDir = EaseDir::In);

	/**
	* @brief フェードイン開始
	* @param[in] durationSec かける秒数
	* @param[in] easeType 補間タイプ
	*/
	void FadeInStart(float durationSec, EaseType easeType = EaseType::Linear, EaseDir easeDir = EaseDir::In);
	
	/**
	* @brief フェード中か
	*/
	bool IsFade() {
		return m_is_fading;
	}

private:
	/**
	* @brief コンストラクタ
	*/
	ScreenFade();

	/**
	* @brief デストラクタ
	*/
	~ScreenFade() = default;

	/**
	* @brief フェード中フラグ
	*/
	bool m_is_fading;

	/**
	* @brief フェードの色
	*/
	DirectX::XMFLOAT4 m_fade_color;

	/**
	* @brief フェード完了にかける秒数
	*/
	float m_duration_sec;

	/**
	* @brief フェードが開始してからの経過秒数
	*/
	float m_progress_sec;

	/**
	* @brief フェードの向き
	*/
	bool m_is_out_dir;

	/**
	* @brief フェードの補間種類
	*/
	EaseType m_ease_type;

	/**
	* @brief 補間種類の向き
	*/
	EaseDir m_ease_dir;
};

}// !namespace HaraProject::Framework

#endif // !_SCREEN_FADE_H_
