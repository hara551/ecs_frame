/**
* @file   SoundManager.h
* @brief  サウンド管理クラス定義.
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
	* @brief サウンド分類
	*/
	enum SoundType
	{
		SE,
		BGM
	};

	/**
	* @brief インスタンス取得
	*/
	static SoundManager& Instance() {
		static SoundManager instance;
		return instance;
	}

	/**
	* @brief 初期化処理
	*/
	void InitSound();

	/**
	* @brief 終了処理
	*/
	void UninitSound();

	/**
	* @brief サウンド読み込み
	* @param[in] soundType サウンド分類 
	* @param[in] fileName ファイル名
	*/
	bool LoadSoundFile(SoundType soundType, std::string fileName);

	/**
	* @brief サウンド再生
	* @param[in] sountType サウンド分類
	* @param[in] fileName ファイル名
	*/
	void Play(SoundType soundType, std::string fileName, bool isLoop = false);

private:
	/**
	* @brief コンストラクタ
	*/
	SoundManager() = default;


	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	/**
	* @brief デストラクタ
	*/
	~SoundManager();

	/**
	* @brief サウンド全体を管理するインタフェース
	*/
	IXAudio2* m_x_audio;

	/**
	* @brief 出力デバイスへの送信用オブジェクト
	*/
	IXAudio2MasteringVoice* m_mastering_voice;

	/**
	* @brief BGM情報
	*/
	std::unordered_map<std::string, AudioClip*> m_name_to_bgm;

	/**
	* @brief SE情報
	*/
	std::unordered_map<std::string, AudioClip*> m_name_to_se;
};

}// !namespace HaraProject::Framework

#endif // !_SOUND_MANAGER_H_
