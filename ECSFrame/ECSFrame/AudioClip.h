/**
* @file   AudioClip.h
* @brief  �T�E���h�f�[�^�A�Đ��I�u�W�F�N�g�Ǘ�.
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
    * @brief �T�E���h���
    */
    struct SoundInfo
    {
        /**
        * @brief �����t�H�[�}�b�g
        */
        WAVEFORMATEX format;

        /**
        * @brief �T�E���h�f�[�^
        */
        BYTE* soundData;

        /**
        * @brief �����f�[�^�̃T�C�Y
        */
        int size;

        /**
        * @brief �Đ��\�ȉ����f�[�^�̒���
        */
        int playLength;
    };

    /**
    * @brief �R���X�g���N�^
    */
    AudioClip(IXAudio2* xAudio, IXAudio2MasteringVoice* masteringVoice);

    /**
    * @brief �f�X�g���N�^
    */
    ~AudioClip();

    /**
    * @brief �T�E���h�f�[�^�ǂݍ���
    * @param[in] filePath �t�@�C���̃p�X
    */
    void Load(std::string filePath);

    /**
    * @brief �T�E���h�Đ�
    * @param[in] isLoop ���[�v�Đ����邩
    */
    void Play(bool isSE, bool isLoop = false);

    /**
    * @brief �S�ẴT�E���h�I�u�W�F�N�g���~
    */
    void StopAll();

private:
    /**
    * @brief �T�E���h���
    */
    SoundInfo m_sound_info;

    /**
    * @brief �Đ��p�I�u�W�F�N�g
    */
    std::vector<IXAudio2SourceVoice*> m_sound_objects;

    /**
    * @brief �T�E���h�S�̂��Ǘ�����C���^�t�F�[�X
    */
    IXAudio2* m_x_audio;

    /**
    * @brief �o�̓f�o�C�X�ւ̑��M�p�I�u�W�F�N�g
    */
    IXAudio2MasteringVoice* m_mastering_voice;

    /**
    * @brief �Đ��I�u�W�F�N�g��񓯊��ɍ폜���邽�߂̃��b�N
    */
    std::mutex m_obj_delete_lock;
};

}
