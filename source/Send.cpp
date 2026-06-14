#include <iostream>
#include <thread>
#include "Send.h"
#include "Viewer.h"
#include "RoundThread.h"
#include <chrono>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

void Send::start() {
	if (m_thread.joinable()) {
		return;
	}
	m_thread = std::thread(&Send::LoopSend, this);
	m_running = true;
}

void Send::stop() {
	if (!m_thread.joinable()) {
		return;
	}
	m_thread.join();
	m_running = false;
}

void Send::LoopSend() {
	auto start = std::chrono::steady_clock::now();
	cv::Mat imflip;
	while (true) {
		auto cur = std::chrono::steady_clock::now();
		SendModel sendModel;
		if (std::chrono::duration_cast<std::chrono::milliseconds>(cur - start).count() > 1000
			&& RoundThread<SendModel>::readThread(sendModel)) {
			cv::flip(sendModel.img, imflip, 1);
			cv::imshow(sendModel.text, imflip);

		}
		cv::waitKey(1);

	}
}