#include <assert.h>
#include <xaudio2.h>

#include "SoundManager.h"
#include "FileUtil.h"

namespace HaraProject::Framework {

/**
* @brief 初期化処理
*/
void SoundManager::InitSound()
{
	// XAudio生成
	XAudio2Create(&m_x_audio, 0);

	// マスタリングボイス生成
	m_x_audio->CreateMasteringVoice(&m_mastering_voice);
}

/**
* @brief 終了処理
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
* @brief サウンド読み込み
* @param[in] soundType サウンド分類
* @param[in] filePath ファイルのパス
*/
bool SoundManager::LoadSoundFile(SoundType soundType, std::string fileName)
{
	// 既に読み込み済みなら成功で終了
	switch (soundType)
	{
	case BGM:
		if (m_name_to_bgm.contains(fileName)) return true;
		break;
	case SE:
		if (m_name_to_se.contains(fileName)) return true;
		break;
	}

	// ファイルの存在確認
	FileType file_type = (soundType == BGM) ? FileType::SoundBGM : FileType::SoundSE;
	if (!FileExists(file_type, fileName.c_str())) return false;

	// AudioClip の作成
	AudioClip* clip = new AudioClip(m_x_audio, m_mastering_voice);
	std::string path = CreatePath(file_type, fileName.c_str());

	clip->Load(path);

	// 登録
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
* @brief サウンド再生
* @param[in] sountType サウンド分類
* @param[in] fileName ファイル名
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
* @brief デストラクタ
*/
SoundManager::~SoundManager()
{
	
}

}//!namespace HaraProject::Framework
