#ifndef SEND_H
#define SEND_H
#include <thread>
#include <atomic>
class Send {
	private:
		std::thread m_thread;
		std::atomic<bool> m_running;
		void LoopSend();
	public:
		~Send() { stop(); }
		void start();
		void stop();
};
#endif