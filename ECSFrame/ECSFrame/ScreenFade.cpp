
#include <DirectXMath.h>

#include "Main.h"
#include "EasingUtil.h"
#include "Defines.h"
#include "SpriteRenderer.h"
#include "ScreenFade.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
ScreenFade::ScreenFade()
	: m_is_fading(false)
	, m_fade_color(0.0f, 0.0f, 0.0f, 1.0f)
	, m_duration_sec(0.0f)
	, m_progress_sec(0.0f)
	, m_is_out_dir(true)
	, m_ease_type(EaseType::Linear)
	, m_ease_dir(EaseDir::In)
{
}

/**
* @brief フェード更新
*/
void ScreenFade::UpdateFade(float deltaTime)
{
	if (!m_is_fading) return;

	// 経過時間を更新
	m_progress_sec += deltaTime;
	// 進行度と向きからα値を算出
	if (m_progress_sec != 0.0f)
	{
		float param = m_progress_sec / m_duration_sec;
		param = Ease(m_ease_type, m_ease_dir, param);

		m_fade_color.w = m_is_out_dir ? param : 1.0f - param;

		if (m_progress_sec >= m_duration_sec)
		{
			m_fade_color.w = m_is_out_dir ? 1.0f : 0.0f;
			m_progress_sec = 0.0f;
			m_duration_sec = 0.0f;
			m_is_fading = false;
		}
	}
}

/**
* @brief フェード描画
*/
void ScreenFade::DrawFade()
{
	RenderTarget* rtv = GetDefaultRTV();
	DepthStencil* dsv = GetDefaultDSV();
	SetRenderTargets(1, &rtv, nullptr);
	SetCullingMode(CULL_NONE);

	HAL::SasakiRyota::SpriteRenderer::SetTexture(nullptr);
	HAL::SasakiRyota::SpriteRenderer::SetSize(DirectX::XMFLOAT2(SCREEN_WIDTH, SCREEN_HEIGHT));
	HAL::SasakiRyota::SpriteRenderer::SetColor(m_fade_color);
	HAL::SasakiRyota::SpriteRenderer::Draw();
}

/**
* @brief フェードアウト開始
* @param[in] seconds かける秒数
* @param[in] rgb 完了時の色
*/
void ScreenFade::FadeOutStart(float durationSec, DirectX::XMFLOAT3 rgb, EaseType easeType, EaseDir easeDir)
{
	m_is_fading = true;
	m_is_out_dir = true;

	m_duration_sec = durationSec;
	m_progress_sec = 0.0f;

	m_fade_color.x = rgb.x;
	m_fade_color.y = rgb.y;
	m_fade_color.z = rgb.z;
	m_fade_color.w = 0.0f;// 不透明度

	m_ease_type = easeType;
}

/**
* @brief フェードイン開始
* @param[in] durationSec かける秒数
* @param[in] easeType 補間タイプ
*/
void ScreenFade::FadeInStart(float durationSec, EaseType easeType, EaseDir easeDir)
{
	m_is_fading = true;
	m_is_out_dir = false;

	m_duration_sec = durationSec;
	m_progress_sec = 0.0f;


	m_fade_color.w = 1.0f;// 不透明度

	m_ease_type = easeType;
}

}// !namespace HaraProject::Framework
