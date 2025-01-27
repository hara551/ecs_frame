
#include <DirectXMath.h>

#include "Main.h"
#include "EasingUtil.h"
#include "Defines.h"
#include "SpriteRenderer.h"
#include "ScreenFade.h"

namespace HaraProject::Framework {

/**
* @brief �R���X�g���N�^
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
* @brief �t�F�[�h�X�V
*/
void ScreenFade::UpdateFade(float deltaTime)
{
	if (!m_is_fading) return;

	// �o�ߎ��Ԃ��X�V
	m_progress_sec += deltaTime;
	// �i�s�x�ƌ������烿�l���Z�o
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
* @brief �t�F�[�h�`��
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
* @brief �t�F�[�h�A�E�g�J�n
* @param[in] seconds ������b��
* @param[in] rgb �������̐F
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
	m_fade_color.w = 0.0f;// �s�����x

	m_ease_type = easeType;
}

/**
* @brief �t�F�[�h�C���J�n
* @param[in] durationSec ������b��
* @param[in] easeType ��ԃ^�C�v
*/
void ScreenFade::FadeInStart(float durationSec, EaseType easeType, EaseDir easeDir)
{
	m_is_fading = true;
	m_is_out_dir = false;

	m_duration_sec = durationSec;
	m_progress_sec = 0.0f;


	m_fade_color.w = 1.0f;// �s�����x

	m_ease_type = easeType;
}

}// !namespace HaraProject::Framework
