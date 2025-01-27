#include <DirectXMath.h>

#include "imgui.h"

#include "ThreadPoolManager.h"
#include "ScreenFade.h"
#include "WorldManager.h"

namespace HaraProject::Framework {

static const float DEFAULT_FADE_OUT_SEC = 0.55f;
static const float DEFAULT_FADE_IN_SEC = 0.55f;

/**
* @brief �S�̍X�V
*/
void WorldManager::Update(float deltaTime)
{
	switch (m_general_state)
	{
	case NomalUpdate:
		UpdateWorlds(deltaTime);
		if (m_world_activate_handle.IsWait())
		{
			// ���[�h��ʂ����ނȂ烍�[�h��ʂ̃��[�h�Ǝ��̃��[���h�̃��[�h���J�n
			if (m_world_activate_handle.NeedShowLoadingScreen())
			{
				if (m_loading_screen_world == nullptr)
				{
					// ���[�h��ʗp���[���h�E�Ăяo�����[���h�����[�h�J�n
					m_loading_screen_world = new WorldBase(m_world_activate_handle.GetLoadingWorldName());
					m_loding_next_world = new WorldBase(m_world_activate_handle.GetWorldName());
					// ���[�h��ʗp���[���h�̃��[�h�҂���Ԃ֕ύX
					m_general_state = ReadyLoadingScreen;
				}
			}
			else
			{
				if (m_loding_next_world == nullptr)
				{
					// �Ăяo�����[���h�����[�h�J�n
					m_loding_next_world = new WorldBase(m_world_activate_handle.GetWorldName());
				}
				// �t�F�[�h���g�p����Ȃ�
				if (m_world_activate_handle.NeedUseFade())
				{
					// �t�F�[�h�A�E�g�J�n
					ScreenFade::Instance().FadeOutStart(DEFAULT_FADE_OUT_SEC, DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
					m_general_state = FadeOut;
				}
				// �t�F�[�h���g�p���Ȃ��Ȃ�
				else
				{
					// ���[�h���I��莟��ʏ�X�V��Ԃ�
					if (m_loding_next_world->IsCompleteLoad())
					{
						// ���[�h�������[���h���A�N�e�B�u�ȃ��[���h�Ƃ��Ēǉ�
						m_current_worlds.push_back(m_loding_next_world);
						m_loding_next_world = nullptr;

						// �n���h�������Z�b�g
						m_world_activate_handle.Reset();
					}
				}
			}
		}
		break;
	case ReadyLoadingScreen:
		UpdateWorlds(deltaTime);
		// ���[�h��ʗp���[���h�̃��[�h������������
		if (m_loading_screen_world->IsCompleteLoad())
		{
			// �t�F�[�h�A�E�g�J�n
			ScreenFade::Instance().FadeOutStart(DEFAULT_FADE_OUT_SEC, DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
			m_general_state = FadeOut;
		}
		break;
	case Loading:
		m_loading_screen_world->UpdateWorld(deltaTime);
		// �Ăяo�����[���h�̃��[�h������������
		if (m_loding_next_world->IsCompleteLoad())
		{
			// ���[�h�������[���h���A�N�e�B�u�ȃ��[���h�Ƃ��Ēǉ�
			m_current_worlds.push_back(m_loding_next_world);
			m_loding_next_world = nullptr;
			// �t�F�[�h�C���J�n
			ScreenFade::Instance().FadeInStart(DEFAULT_FADE_IN_SEC);
			m_general_state = FadeIn;
		}
		break;
	case FadeOut:
		if (ScreenFade::Instance().IsFade())
		{
			// �t�F�[�h���͍X�V�����̂ݍs���I��
			UpdateWorlds(deltaTime);
			ScreenFade::Instance().UpdateFade(deltaTime);
			return;
		}
		// ����ւ����[�h�Ȃ�
		if (m_world_activate_handle.GetActivateMode() == WorldActivateHandle::Change)
		{
			// ��ԏ�̃��[���h���폜
			if (!m_current_worlds.empty())
			{
				ReleaseWorld(m_current_worlds.back()->GetName());
			}
		}

		// ���[�h��ʂ����܂Ȃ��ꍇ
		if (!m_world_activate_handle.NeedShowLoadingScreen())
		{
			// �t�F�[�h�A�E�g�����܂܃��[�h��҂��A����������
			if (m_loding_next_world->IsCompleteLoad())
			{
				// ���[�h�������[���h���A�N�e�B�u�ȃ��[���h�Ƃ��Ēǉ�
				m_current_worlds.push_back(m_loding_next_world);
				m_loding_next_world = nullptr;
				// �t�F�[�h�C���J�n
				ScreenFade::Instance().FadeInStart(DEFAULT_FADE_IN_SEC);
				m_general_state = FadeIn;
			}
		}
		// ���[�h��ʂ����ޏꍇ
		else
		{
			// ��Ԃ����[�h���ɕύX
			m_general_state = Loading;
		}
		break;
	case FadeIn:
		UpdateWorlds(deltaTime);
		if (ScreenFade::Instance().IsFade())
		{
			// �t�F�[�h���͍X�V�����݂̂��s���I��
			ScreenFade::Instance().UpdateFade(deltaTime);
			return;
		}
		// �n���h�������Z�b�g
		m_world_activate_handle.Reset();
		// �t�F�[�h�C���������������Ԃ�ʏ�X�V�ɕύX
		m_general_state = NomalUpdate;
		break;
	}
}

/**
* @brief �S�̕`��
*/
void WorldManager::Draw()
{
	switch (m_general_state)
	{
	case NomalUpdate:
		DrawWorlds();
		break;
	case Loading:
		m_loading_screen_world->DrawWorld();
		break;
	case FadeOut:
	case FadeIn:
		DrawWorlds();
		ScreenFade::Instance().DrawFade();
		break;
	}
}

/**
* @brief �A�N�e�B�u�ȃ��[���h���X�V
*/
void WorldManager::UpdateWorlds(float deltaTime)
{
	for (const auto& world : m_current_worlds)
	{
		world->UpdateWorld(deltaTime);
	}
}

/**
* @brief �A�N�e�B�u�ȃ��[���h��`��
*/
void WorldManager::DrawWorlds()
{
	for (const auto& world : m_current_worlds)
	{
		world->DrawWorld();
	}
}

/**
* @brief �ŏ��̃��[���h���N��
*/
void WorldManager::ActivateBeginningWorld()
{
	// �ŏ��ɌĂԃ��[���h�����擾
	std::string world_name = m_edit_data_manager.LoadBeginningWorldName();
	// �N��
	ActivateWorld(world_name, WorldActivateHandle::Change, false);
}

/**
* @brief ���[���h���������
* @param[in] worldTag ���[���h��
*/
void WorldManager::ReleaseWorld(std::string worldName)
{
	// �w��̃��[���h��������ėv�f���폜����
	std::erase_if(m_current_worlds, 
		[worldName](WorldBase* world)
		{
			if (world->GetName() == worldName)
			{
				delete world;
				return true;
			}
			return false;
		});
}

/**
* @brief �S���[���h�����
*/
void WorldManager::ReleaseAllWorlds()
{
	for (auto& world : m_current_worlds)
	{
		if (world != nullptr)
		{
			delete world;
			world = nullptr;
		}
	}
	m_current_worlds.clear();
}

/**
* @brief ���̃��[���h�Ăяo������ݒ�
* @param[in] worldName ���[���h��
* @param[in] mode �Ăяo�����[�h
*/
void WorldManager::ActivateWorld(std::string worldName, WorldActivateHandle::ActivateMode mode, bool useFade, bool showLoadingScreen, std::string loadingWorldName)
{
	m_world_activate_handle.Set(worldName, mode, useFade, showLoadingScreen, loadingWorldName);
}

/**
* @brief �R���X�g���N�^
*/
WorldManager::WorldManager()
	: m_loading_screen_world(nullptr)
	, m_loding_next_world(nullptr)
	, m_general_state(NomalUpdate)
{
}

/**
* @brief �f�X�g���N�^
*/
WorldManager::~WorldManager()
{
	ReleaseAllWorlds();
}

/**
* @brief ���[���h���d�˂�
* @param[in] worldName ���[���h��
*/
void WorldManager::AdditiveWorld(std::string worldName)
{
	m_current_worlds.push_back(new WorldBase(worldName));
}

}// namespace HaraProject::Framework