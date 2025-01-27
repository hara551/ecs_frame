/**
* @file   AudioClip.h
* @brief  サウンドデータ、再生オブジェクト管理.
* @author Hara Sota.
* @date   2024/10/17
*/
#include <xaudio2.h>

#include <string>
#include <vector>
#include <mutex>

namespace HaraProject::Framework {

class AudioClip
{
public:
    /**
    * @brief サウンド情報
    */
    struct SoundInfo
    {
        /**
        * @brief 音声フォーマット
        */
        WAVEFORMATEX format;

        /**
        * @brief サウンドデータ
        */
        BYTE* soundData;

        /**
        * @brief 音声データのサイズ
        */
        int size;

        /**
        * @brief 再生可能な音声データの長さ
        */
        int playLength;
    };

    /**
    * @brief コンストラクタ
    */
    AudioClip(IXAudio2* xAudio, IXAudio2MasteringVoice* masteringVoice);

    /**
    * @brief デストラクタ
    */
    ~AudioClip();

    /**
    * @brief サウンドデータ読み込み
    * @param[in] filePath ファイルのパス
    */
    void Load(std::string filePath);

    /**
    * @brief サウンド再生
    * @param[in] isLoop ループ再生するか
    */
    void Play(bool isSE, bool isLoop = false);

    /**
    * @brief 全てのサウンドオブジェクトを停止
    */
    void StopAll();

private:
    /**
    * @brief サウンド情報
    */
    SoundInfo m_sound_info;

    /**
    * @brief 再生用オブジェクト
    */
    std::vector<IXAudio2SourceVoice*> m_sound_objects;

    /**
    * @brief サウンド全体を管理するインタフェース
    */
    IXAudio2* m_x_audio;

    /**
    * @brief 出力デバイスへの送信用オブジェクト
    */
    IXAudio2MasteringVoice* m_mastering_voice;

    /**
    * @brief 再生オブジェクトを非同期に削除するためのロック
    */
    std::mutex m_obj_delete_lock;
};

}
