#include <assert.h>
#include <xaudio2.h>

#include "SoundManager.h"
#include "FileUtil.h"

namespace HaraProject::Framework {

/**
* @brief ����������
*/
void SoundManager::InitSound()
{
	// XAudio����
	XAudio2Create(&m_x_audio, 0);

	// �}�X�^�����O�{�C�X����
	m_x_audio->CreateMasteringVoice(&m_mastering_voice);
}

/**
* @brief �I������
*/
void SoundManager::UninitSound()
{
	for (auto& [name, audio] : m_name_to_se)
	{
		if (audio != nullptr)
		{
			delete audio;
			audio = nullptr;
		}
	}
	for (auto& [name, audio] : m_name_to_bgm)
	{
		if (audio != nullptr)
		{
			delete audio;
			audio = nullptr;
		}
	}
	m_mastering_voice->DestroyVoice();
	m_x_audio->Release();
}

/**
* @brief �T�E���h�ǂݍ���
* @param[in] soundType �T�E���h����
* @param[in] filePath �t�@�C���̃p�X
*/
bool SoundManager::LoadSoundFile(SoundType soundType, std::string fileName)
{
	// ���ɓǂݍ��ݍς݂Ȃ琬���ŏI��
	switch (soundType)
	{
	case BGM:
		if (m_name_to_bgm.contains(fileName)) return true;
		break;
	case SE:
		if (m_name_to_se.contains(fileName)) return true;
		break;
	}

	// �t�@�C���̑��݊m�F
	FileType file_type = (soundType == BGM) ? FileType::SoundBGM : FileType::SoundSE;
	if (!FileExists(file_type, fileName.c_str())) return false;

	// AudioClip �̍쐬
	AudioClip* clip = new AudioClip(m_x_audio, m_mastering_voice);
	std::string path = CreatePath(file_type, fileName.c_str());

	clip->Load(path);

	// �o�^
	switch (soundType)
	{
	case BGM:
		m_name_to_bgm[fileName] = clip;
		break;
	case SE:
		m_name_to_se[fileName] = clip;
		break;
	}

	return true;
}

/**
* @brief �T�E���h�Đ�
* @param[in] sountType �T�E���h����
* @param[in] fileName �t�@�C����
*/
void SoundManager::Play(SoundType soundType, std::string fileName, bool isLoop)
{
	switch (soundType)
	{
	case SE: 
		if (m_name_to_se.contains(fileName))
		{
			m_name_to_se[fileName]->Play(true, isLoop);
		}
		return;
	case BGM:
		if (m_name_to_bgm.contains(fileName))
		{
			m_name_to_bgm[fileName]->Play(false, isLoop);
		}
		return;
	}
}

/**
* @brief �f�X�g���N�^
*/
SoundManager::~SoundManager()
{
	
}

}//!namespace HaraProject::Framework
