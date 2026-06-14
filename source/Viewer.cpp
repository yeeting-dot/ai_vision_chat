#include <iostream>
#include <thread>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "RoundThread.h"
#include <chrono>
#include "Viewer.h"

void Viewer::start() {
	if (m_thread.joinable()) {
		return;
	}
	m_thread = std::thread(&Viewer::LoopViewer, this);
	m_running = true;
}

void Viewer::stop() {
	if (!m_thread.joinable()) {
		return;
	}
	m_thread.join();
	m_running = false;
	return;
}

void Viewer::LoopViewer() {
	cv::Mat img,imflip;
	cv::VideoCapture cap(0);
	auto start = std::chrono::steady_clock::now();
	while (cap.read(img)) {
		auto cur = std::chrono::steady_clock::now();
		std::string text;
		if (std::chrono::duration_cast<std::chrono::microseconds>(cur - start).count() > 1000
			&& RoundThread<std::string>::readThread(text)) {
			sendModel.text = text;
			sendModel.img = img.clone();
			RoundThread<SendModel>::writeThread(sendModel);
			start = cur;
		}
		cv::flip(img,imflip,1);
		cv::imshow("IMG", imflip);
		cv::waitKey(1);
	}
}