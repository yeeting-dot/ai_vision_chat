#ifndef AUDIO_TRANSLATE_H
#define AUDIO_TRANSLATE_H
#include "RoundThread.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <atomic>
#include <thread>
#include <whisper.h>
class AudioTranslate {
	private:
		const static int CHECK_PER_LOOP = 1000;
		whisper_context* m_ctx = nullptr;
		std::atomic<bool> m_running { false };
		std::thread m_thread;
		void LoopCheck();	
	public:
		AudioTranslate(const std::string& path) {
			m_ctx = whisper_init_from_file(path.c_str());
			if (!m_ctx) {
				std::cerr << "Error load model!" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		~AudioTranslate();
		bool start();
		bool stop();

};

#endif