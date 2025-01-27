/**
* @file ScreenFade.h
* @brief ��ʂ̃t�F�[�h����
* @author HaraSota
* @date 2024/11/09
*/
#ifndef _SCREEN_FADE_H_
#define _SCREEN_FADE_H_

#include <DirectXMath.h>

#include "EasingUtil.h"

namespace HaraProject::Framework {

/**
* @brief ��ʃt�F�[�h�N���X
* @attention �V���O���g��
*/
class ScreenFade 
{
public:
	/**
	* @brief �R�s�[�R���X�g���N�^�֎~
	*/
	ScreenFade(const ScreenFade&) = delete;

	/**
	* @brief ����֎~
	*/
	ScreenFade& operator=(const ScreenFade&) = delete;

	/**
	* @brief �C���X�^���X�擾
	*/
	static ScreenFade& Instance()
	{
		static ScreenFade instance;
		return instance;
	}

	/**
	* @brief �t�F�[�h�X�V
	*/
	void UpdateFade(float deltaTime);

	/**
	* @brief �t�F�[�h�`��
	*/
	void DrawFade();

	/**
	* @brief �t�F�[�h�A�E�g�J�n
	* @param[in] durationSec ������b��
	* @param[in] rgb �������̐F
	* @param[in] easeType ��ԃ^�C�v
	*/
	void FadeOutStart(float durationSec, DirectX::XMFLOAT3 rgb, EaseType easeType = EaseType::Linear, EaseDir easeDir = EaseDir::In);

	/**
	* @brief �t�F�[�h�C���J�n
	* @param[in] durationSec ������b��
	* @param[in] easeType ��ԃ^�C�v
	*/
	void FadeInStart(float durationSec, EaseType easeType = EaseType::Linear, EaseDir easeDir = EaseDir::In);
	
	/**
	* @brief �t�F�[�h����
	*/
	bool IsFade() {
		return m_is_fading;
	}

private:
	/**
	* @brief �R���X�g���N�^
	*/
	ScreenFade();

	/**
	* @brief �f�X�g���N�^
	*/
	~ScreenFade() = default;

	/**
	* @brief �t�F�[�h���t���O
	*/
	bool m_is_fading;

	/**
	* @brief �t�F�[�h�̐F
	*/
	DirectX::XMFLOAT4 m_fade_color;

	/**
	* @brief �t�F�[�h�����ɂ�����b��
	*/
	float m_duration_sec;

	/**
	* @brief �t�F�[�h���J�n���Ă���̌o�ߕb��
	*/
	float m_progress_sec;

	/**
	* @brief �t�F�[�h�̌���
	*/
	bool m_is_out_dir;

	/**
	* @brief �t�F�[�h�̕�Ԏ��
	*/
	EaseType m_ease_type;

	/**
	* @brief ��Ԏ�ނ̌���
	*/
	EaseDir m_ease_dir;
};

}// !namespace HaraProject::Framework

#endif // !_SCREEN_FADE_H_
