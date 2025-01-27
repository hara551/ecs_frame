
#include <string>
#include "WorldActivateHandle.h"

namespace HaraProject::Framework {

/**
 * @brief �R���X�g���N�^
 */
WorldActivateHandle::WorldActivateHandle()
	: m_activate_mode(Change)
	, m_world_name("")
	, m_use_fade(true)
	, m_show_loading_screen(false)
	, m_loading_world_name("")
	, m_is_wait(false)
{
}

/**
 * @brief �p�����[�^��ݒ�
 * @param[in] worldName ���[���h��
 * @param[in] mode �؂�ւ����[�h
 * @param[in] useFade �t�F�[�h���g�p���邩
 * @param[in] showLoadingScreen ���[�f�B���O��ʂ�\�����邩
 * @param[in] loadingWorldName ���[�f�B���O��ʗp�̃��[���h��
 */
void WorldActivateHandle::Set(const std::string& worldName, ActivateMode mode, bool useFade, bool showLoadingScreen, const std::string& loadingWorldName)
{
	m_world_name = worldName;
	m_activate_mode = mode;
	m_use_fade = useFade;
	m_show_loading_screen = showLoadingScreen;
	m_loading_world_name = loadingWorldName;
	m_is_wait = true;
}

/**
 * @brief ������ԂɃ��Z�b�g
 */
void WorldActivateHandle::Reset()
{
	m_world_name = "";
	m_use_fade = true;
	m_show_loading_screen = false;
	m_loading_world_name = "";
	m_is_wait = false;
}

} // namespace HaraProject::Framework