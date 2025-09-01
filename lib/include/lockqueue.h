#pragma once
#include <queue>
#include <thread>
#include <mutex>	//pthread_mutex_t
#include <condition_variable>	//pthread_condition_t

// 异步写日志的日志队列
template<typename T>
class LockQueue
{
public:
	// 多个worker线程都会写日志queue
	void Push(const T &data)
	{
		std::lock_guard<std::mutex> lg(m_mutex);
		m_queue.push(data);
		m_cond.notify_one(); // 唤醒一个等待的线程
	}
	// 一个线程读日志queue，写日志文件
	T Pop()
	{
		std::unique_lock<std::mutex> ul(m_mutex);
		while (m_queue.empty())
		{
			// 日志队列为空，线程进入wait状态
			m_cond.wait(ul);
		}

		T data = m_queue.front();
		m_queue.pop();
		return data;
	}
private:
	std::queue<T> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_cond;
};