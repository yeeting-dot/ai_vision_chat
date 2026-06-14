#include "AudioTranslate.h"
#include "AudioTake.h"
#include "RoundThread.h"
#include <thread>
#include <chrono>
#include <iostream>

void AudioTranslate::LoopCheck() {
	auto start = std::chrono::system_clock::now();
	whisper_full_params params = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
	params.language = "zh";
	params.n_threads = 4;
	params.initial_prompt = "以下是普通话的句子。";
	while (true) {
		auto cur = std::chrono::system_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(cur - start).count()
			< CHECK_PER_LOOP) continue;
		start = cur;
		VoiceMess mes;
		if (!RoundThread<VoiceMess>::readThread(mes)) { continue; }
		std::cout << "Size of data" << mes.dataLength << std::endl;
		static int fileCounter = 0;
		if (whisper_full(m_ctx, params, mes.voiceData.data(), mes.dataLength) == 0) {
			const int n_segments = whisper_full_n_segments(m_ctx);
			std::string result;
			for (int i = 0; i < n_segments; i++) {
				const char* text = whisper_full_get_segment_text(m_ctx, i);
				result += text;
			}
			std::cout << result << std::endl;
			RoundThread<std::string>::writeThread(result);
		}
		else {
			std::cerr << "Whisper transcation Failed" << std::endl;
		}

	}
}

bool AudioTranslate::start() {
	if (m_thread.joinable()) {
		return true;
	}
	m_thread = std::thread(&AudioTranslate::LoopCheck, this);
	m_running = true;
	return true;
}

bool AudioTranslate::stop() {
	if (!m_thread.joinable()) {
		return false;
	}
	m_thread.join();
	m_running = false;
}

AudioTranslate::~AudioTranslate() {
	stop();
	if (m_ctx) {
		whisper_free(m_ctx);
	}
}
