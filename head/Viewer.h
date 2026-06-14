#ifndef VIEWER_H
#define VIEWER_H
#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <thread>
#include <atomic>


typedef struct SendModel {
	std::string text;
	cv::Mat img;
} SendModel;

class Viewer {
	private:
		std::thread m_thread;
		std::atomic<bool> m_running;
		SendModel sendModel;
		void LoopViewer();
	public:
		~Viewer() { stop(); }
		void start();
		void stop();
};
#endif
