/**
* @file   SoundManager.h
* @brief  �T�E���h�Ǘ��N���X��`.
* @author Hara Sota.
* @date   2024/10/17
*/
#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include <xaudio2.h>

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

#include "AudioClip.h"

namespace HaraProject::Framework {

class SoundManager
{
public:
	/**
	* @brief �T�E���h����
	*/
	enum SoundType
	{
		SE,
		BGM
	};

	/**
	* @brief �C���X�^���X�擾
	*/
	static SoundManager& Instance() {
		static SoundManager instance;
		return instance;
	}

	/**
	* @brief ����������
	*/
	void InitSound();

	/**
	* @brief �I������
	*/
	void UninitSound();

	/**
	* @brief �T�E���h�ǂݍ���
	* @param[in] soundType �T�E���h���� 
	* @param[in] fileName �t�@�C����
	*/
	bool LoadSoundFile(SoundType soundType, std::string fileName);

	/**
	* @brief �T�E���h�Đ�
	* @param[in] sountType �T�E���h����
	* @param[in] fileName �t�@�C����
	*/
	void Play(SoundType soundType, std::string fileName, bool isLoop = false);

private:
	/**
	* @brief �R���X�g���N�^
	*/
	SoundManager() = default;


	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	/**
	* @brief �f�X�g���N�^
	*/
	~SoundManager();

	/**
	* @brief �T�E���h�S�̂��Ǘ�����C���^�t�F�[�X
	*/
	IXAudio2* m_x_audio;

	/**
	* @brief �o�̓f�o�C�X�ւ̑��M�p�I�u�W�F�N�g
	*/
	IXAudio2MasteringVoice* m_mastering_voice;

	/**
	* @brief BGM���
	*/
	std::unordered_map<std::string, AudioClip*> m_name_to_bgm;

	/**
	* @brief SE���
	*/
	std::unordered_map<std::string, AudioClip*> m_name_to_se;
};

}// !namespace HaraProject::Framework

#endif // !_SOUND_MANAGER_H_
