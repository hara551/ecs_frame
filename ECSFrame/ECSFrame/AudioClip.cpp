#include <xaudio2.h>
#include <assert.h>
#include <mutex>

#include "AudioClip.h"
#include "ThreadPoolManager.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
AudioClip::AudioClip(IXAudio2* xAudio, IXAudio2MasteringVoice* masteringVoice)
	: m_x_audio(xAudio)
	, m_mastering_voice(masteringVoice)
{
}

/**
* @brief デストラクタ
*/
AudioClip::~AudioClip()
{
	for (IXAudio2SourceVoice* sound_object : m_sound_objects)
	{
		sound_object->Stop();
		sound_object->DestroyVoice();
	}

	delete[] m_sound_info.soundData;
}

/**
* @brief サウンドデータ読み込み
* @param[in] filePath ファイルのパス
*/
void AudioClip::Load(std::string filePath)
{
	{
		HMMIO hmmio = NULL;
		MMIOINFO mmioinfo = { 0 };
		MMCKINFO riffchunkinfo = { 0 };
		MMCKINFO datachunkinfo = { 0 };
		MMCKINFO mmckinfo = { 0 };
		UINT32 buflen;
		LONG readlen;

		hmmio = mmioOpenA((LPSTR)filePath.c_str(), &mmioinfo, MMIO_READ);
		assert(hmmio);

		riffchunkinfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(hmmio, &riffchunkinfo, NULL, MMIO_FINDRIFF);

		mmckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(hmmio, &mmckinfo, &riffchunkinfo, MMIO_FINDCHUNK);

		if (mmckinfo.cksize >= sizeof(WAVEFORMATEX)) {
			mmioRead(hmmio, (HPSTR)&m_sound_info.format, sizeof(m_sound_info.format));
		}
		else {
			PCMWAVEFORMAT pcmwf = { 0 };
			mmioRead(hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
			memset(&m_sound_info.format, 0x00, sizeof(m_sound_info.format));
			memcpy(&m_sound_info.format, &pcmwf, sizeof(pcmwf));
			m_sound_info.format.cbSize = 0;
		}
		mmioAscend(hmmio, &mmckinfo, 0);

		datachunkinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hmmio, &datachunkinfo, &riffchunkinfo, MMIO_FINDCHUNK);

		buflen = datachunkinfo.cksize;
		m_sound_info.soundData = new unsigned char[buflen];
		readlen = mmioRead(hmmio, (HPSTR)m_sound_info.soundData, buflen);

		m_sound_info.size = readlen;
		m_sound_info.playLength = readlen / m_sound_info.format.nBlockAlign;

		mmioClose(hmmio, 0);
	}
}

/**
* @brief サウンド再生
* @param[in] isLoop ループ再生するか
*/
void AudioClip::Play(bool isSE, bool isLoop)
{
	// 新しい SourceVoice を作成
	IXAudio2SourceVoice* new_source_voice = nullptr;
	HRESULT hr = m_x_audio->CreateSourceVoice(&new_source_voice, &m_sound_info.format);
	assert(SUCCEEDED(hr));

	// バッファ設定
	XAUDIO2_BUFFER bufinfo = {};
	bufinfo.AudioBytes = m_sound_info.size;
	bufinfo.pAudioData = m_sound_info.soundData;
	bufinfo.PlayBegin = 0;
	bufinfo.PlayLength = m_sound_info.playLength;

	if (isLoop) 
	{
		bufinfo.LoopBegin = 0;
		bufinfo.LoopLength = m_sound_info.playLength;
		bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	new_source_voice->SubmitSourceBuffer(&bufinfo, NULL);
	new_source_voice->SetVolume(1.0f);
	new_source_voice->Start();

	m_sound_objects.push_back(new_source_voice);

	if (!isSE) return;

	// 再生終了に再生オブジェクトを削除するよう依頼
	ThreadPoolManager::Instance().Enqueue(ThreadPoolManager::Event, 
		[&, new_source_voice]()
		{
			for (;;)
			{
				XAUDIO2_VOICE_STATE state;
				new_source_voice->GetState(&state);
				if (state.BuffersQueued == 0)
				{
					new_source_voice->Stop();
					new_source_voice->DestroyVoice();
					{
						std::lock_guard<std::mutex> lock(m_obj_delete_lock);

						std::erase_if(m_sound_objects, [new_source_voice](auto* obj) {return obj == new_source_voice; });
					}
					return;
				}
			}
		});
}

/**
* @brief 全てのサウンドオブジェクトを停止
*/
void AudioClip::StopAll()
{
	for (auto& sound_object : m_sound_objects)
	{
		sound_object->Stop();
	}
}

}//!namespace HaraProject::Framework