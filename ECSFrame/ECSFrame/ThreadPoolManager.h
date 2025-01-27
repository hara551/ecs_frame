/**
* @file ThreadPoolManager.h
* @brief �X���b�h�v�[�����񓯊������Ǘ�
* @author HaraSota
* @date 2024/11/09
*/
#ifndef _THREAD_POOL_MANAGER_H_
#define _THREAD_POOL_MANAGER_H_

#include <cstdint>
#include <queue>
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>
#include <functional>
#include <vector>

namespace HaraProject::Framework {

class ThreadPoolManager
{
public:
	/**
	* @brief �����̕���(�����������D��)
	*/
	enum ProcessType
	{
		Event,
		Load,
		AnyTime,
		MAX_PROCESS_TYPE
	};

	/**
	* @brief �T�|�[�g����Ă���X���b�h�����擾�ł��Ȃ������ۂɓK�����鐔
	*/
	static constexpr uint32_t DEFAULT_NUM_THREAD = 2;

public:
	/**
	* @brief �C���X�^���X�擾
	*/
	static ThreadPoolManager& Instance() {
		static ThreadPoolManager instance;
		return instance;
	}

	/**
	* @brief �^�X�N�����s�҂��s��ɒǉ�
	* @param[in] f �^�X�N�Ƃ��Ēǉ�����֐�
	* @param[in] args �ǉ�����֐��̈���
	*/
	template<typename F, typename... Args>
	void Enqueue(ProcessType type, F&& f, Args&&... args);

private:
	/**
	* @brief �R���X�g���N�^
	* @param[in] numThread �쐬����X���b�h��
	*/
	ThreadPoolManager(uint32_t numThread = std::thread::hardware_concurrency());

	/**
	* @brief �f�X�g���N�^
	*/
	~ThreadPoolManager();

	/**
	* @brief �v�[�����̊e�X���b�h�Ɋ��蓖�Ă���^�X�N�������s����
	*/
	void ThreadWork();

	/**
	* @brief ���s�҂��^�X�N�����݂��邩
	*/
	bool IsEmptyTaskQueue();

	/**
	* @brief ��ԏ�̃^�X�N���擾����
	*/
	std::function<void()> FrontTask();

	ThreadPoolManager(const ThreadPoolManager&) = delete;
	ThreadPoolManager& operator=(const ThreadPoolManager&) = delete;

private:
	/**
	* @brief �X���b�h
	*/
	std::vector<std::thread> m_threads;

	/**
	* @brief �������ނ��Ƃ̎��s�҂��^�X�N�s��
	*/
	std::vector<std::queue<std::function<void()>>> m_task_queue;

	/**
	* @brief �^�X�N�s��ւ̃A�N�Z�X��ی삷�郍�b�N
	*/
	std::mutex m_queue_mutex;

	/**
	* @brief �^�X�N�s��̏��
	*/
	std::condition_variable m_queue_condition;

	/**
	* @brief �X���b�h�I���t���O
	*/
	bool m_is_shutting_down;

	/**
	* @brief �X���b�h��
	*/
	uint32_t m_num_threads;
};

template<typename F, typename ...Args>
inline void ThreadPoolManager::Enqueue(ProcessType type, F&& f, Args&&... args)
{
	{
		std::lock_guard<std::mutex> lock(m_queue_mutex);

		m_task_queue[type].emplace(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
	}
	m_queue_condition.notify_one();
}

}// namespace HaraProject::Framework

#endif // !_THREAD_POOL_MANAGER_H_
