/**
* @file   WorldActivateHandle.h
* @brief  ���[���h�̌Ăяo�����Ǘ��N���X��`.
* @author Hara Sota.
* @date   2024/10/17
*/
#ifndef _WORLD_ACTIVATE_HANDLE_H_
#define _WORLD_ACTIVATE_HANDLE_H_

#include <string>

namespace HaraProject::Framework {

/**
 * @brief ���[���h�̌Ăяo�������Ǘ�����N���X
 */
class WorldActivateHandle
{
public:
    /**
     * @brief ���[���h�̌Ăяo�����[�h
     */
    enum ActivateMode
    {
        Change,   // ���݂̃��[���h��؂�ւ���
        Additive  // ���݂̃��[���h�ɒǉ�����
    };

    /**
     * @brief �R���X�g���N�^
     */
    WorldActivateHandle();

    /**
     * @brief �p�����[�^��ݒ�
     * @param[in] worldName ���[���h��
     * @param[in] mode �؂�ւ����[�h
     * @param[in] useFade �t�F�[�h���g�p���邩
     * @param[in] showLoadingScreen ���[�f�B���O��ʂ�\�����邩
     * @param[in] loadingWorldName ���[�f�B���O��ʗp�̃��[���h��
     */
    void Set(const std::string& worldName, ActivateMode mode, bool useFade, bool showLoadingScreen, const std::string& loadingWorldName = "");

    /**
     * @brief ������ԂɃ��Z�b�g
     */
    void Reset();

    /**
    * @brief �Ăяo�����[���h�����擾
    */
    std::string GetWorldName() {
        return m_world_name;
    }

    /**
    * @brief �Ăяo�����[�h�擾
    */
    ActivateMode GetActivateMode() {
        return m_activate_mode;
    }

    /**
    * @brief �t�F�[�h�g�p�t���O�擾
    */
    bool NeedUseFade() {
        return m_use_fade;
    }

    /**
    * @brief ���[�h��ʕ\���t���O�擾
    */
    bool NeedShowLoadingScreen() {
        return m_show_loading_screen;
    }

    /**
    * @brief ���[�h��ʗp���[���h�̖��O���擾
    */
    std::string GetLoadingWorldName() {
        return m_loading_world_name;
    }

    /**
    * @brief �Ăяo���ҋ@����
    */
    bool IsWait() {
        return m_is_wait;
    }

    /**
    * @brief �ҋ@��Ԃ�ݒ�
    */
    void SetIsWait(bool isWait) {
        m_is_wait = isWait;
    }

private:
    /**
    * @brief �Ăяo�����[���h�̖��O
    */
    std::string m_world_name;

    /**
    * @brief �Ăяo�����[�h
    */
    ActivateMode m_activate_mode;   

    /**
    * @brief �t�F�[�h���g�p���邩
    */
    bool m_use_fade;             

    /**
    * @brief ���[�h��ʂ�\�����邩
    */
    bool m_show_loading_screen;    

    /**
    * @brief �\�����郍�[�h��ʗp���[���h�̖��O
    */
    std::string m_loading_world_name; 

    /**
    * @brief �Ăяo���ҋ@����
    */
    bool m_is_wait;
};

} // namespace HaraProject::Framework

#endif // !_WORLD_ACTIVATE_HANDLE_H_
