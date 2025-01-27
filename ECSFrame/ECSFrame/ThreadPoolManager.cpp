#include <cstdint>
#include <queue>
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>
#include <functional>
#include <vector>
#include <iostream>

#include "ThreadPoolManager.h"

namespace HaraProject::Framework {

/**
* @brief �R���X�g���N�^
* @param[in] numThread �쐬����X���b�h��
*/
ThreadPoolManager::ThreadPoolManager(uint32_t numThread)
	: m_num_threads(numThread == 0 ? DEFAULT_NUM_THREAD : std::thread::hardware_concurrency())
	, m_is_shutting_down(false)
{
	// �������ނ��ƂɃL���[���쐬
	{
		std::lock_guard<std::mutex> lock(m_queue_mutex);
		m_task_queue.resize(MAX_PROCESS_TYPE);
	}

	// �X���b�h�쐬
	for (int i = 0; i < m_num_threads; ++i)
	{
		m_threads.emplace_back(std::bind(&ThreadPoolManager::ThreadWork, this));
	}
}

/**
* @brief �f�X�g���N�^
*/
ThreadPoolManager::~ThreadPoolManager()
{
	{
		std::lock_guard<std::mutex> lock(m_queue_mutex);
		m_is_shutting_down = true;
	}
	m_queue_condition.notify_all();

	for (std::thread& thread : m_threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}

/**
* @brief �v�[�����̊e�X���b�h�Ɋ��蓖�Ă���^�X�N�������s����
*/
void ThreadPoolManager::ThreadWork()
{
	for (;;)
	{
		std::function<void()> task;

		{// ���b�N�p�ɃX�R�[�v��؂�
			std::unique_lock<std::mutex> queueLock(m_queue_mutex);

			// �X���b�h�I�����܂��̓^�X�N���ǉ������܂őҋ@
			m_queue_condition.wait(queueLock, [this] {return m_is_shutting_down || !IsEmptyTaskQueue(); });

			// �I���t���O�������Ă��ăL���[����Ȃ烋�[�v�𔲂���
			if (m_is_shutting_down && IsEmptyTaskQueue())
			{
				return;
			}

			// �擪�̃^�X�N���擾
			task = FrontTask();
		}
		// �^�X�N�����s
		task();
	}
}

/**
* @brief ���s�҂��^�X�N�����݂��邩
*/
bool ThreadPoolManager::IsEmptyTaskQueue()
{
	for (int i = 0; i < MAX_PROCESS_TYPE; ++i)
	{
		if (!m_task_queue[i].empty())
		{
			return false;
		}
	}
	return true;
}

/**
* @brief ��ԏ�̃^�X�N���擾����
*/
std::function<void()> ThreadPoolManager::FrontTask()
{
	std::function<void()> task;
	for (int i = 0; i < MAX_PROCESS_TYPE; ++i)
	{
		if (!m_task_queue[i].empty())
		{
			task = m_task_queue[i].front();
			m_task_queue[i].pop();
		}
	}
	return task;
}

}// namespace HaraProject::Framework
