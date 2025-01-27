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
* @brief コンストラクタ
* @param[in] numThread 作成するスレッド数
*/
ThreadPoolManager::ThreadPoolManager(uint32_t numThread)
	: m_num_threads(numThread == 0 ? DEFAULT_NUM_THREAD : std::thread::hardware_concurrency())
	, m_is_shutting_down(false)
{
	// 処理分類ごとにキューを作成
	{
		std::lock_guard<std::mutex> lock(m_queue_mutex);
		m_task_queue.resize(MAX_PROCESS_TYPE);
	}

	// スレッド作成
	for (int i = 0; i < m_num_threads; ++i)
	{
		m_threads.emplace_back(std::bind(&ThreadPoolManager::ThreadWork, this));
	}
}

/**
* @brief デストラクタ
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
* @brief プール内の各スレッドに割り当てられるタスク逐次実行処理
*/
void ThreadPoolManager::ThreadWork()
{
	for (;;)
	{
		std::function<void()> task;

		{// ロック用にスコープを切る
			std::unique_lock<std::mutex> queueLock(m_queue_mutex);

			// スレッド終了時またはタスクが追加されるまで待機
			m_queue_condition.wait(queueLock, [this] {return m_is_shutting_down || !IsEmptyTaskQueue(); });

			// 終了フラグが立っていてキューが空ならループを抜ける
			if (m_is_shutting_down && IsEmptyTaskQueue())
			{
				return;
			}

			// 先頭のタスクを取得
			task = FrontTask();
		}
		// タスクを実行
		task();
	}
}

/**
* @brief 実行待ちタスクが存在するか
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
* @brief 一番上のタスクを取得する
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
