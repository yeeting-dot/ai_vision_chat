#ifndef ROUND_THREAD
#define ROUND_THREAD
#include <vector>
#include "AudioTake.h"
#include "Send.h"
#include "Viewer.h"
using std::vector;

template <typename T>
class RoundThread{
	private:
		inline static int read = 0;
		inline static int write = 0;
		inline static vector<T> messages = vector<T>(10);

	public:
		static void writeThread(const T& voiceMess);
		static bool readThread(T& have);
};
template <typename T>
void RoundThread<T>::writeThread(const T& voiceMess) {
	if ((write + 1) % 10 == read) {
		return;
	}
	messages[write] = voiceMess;
	write = ((write + 1) % 10);
}
template<typename T>
bool RoundThread<T>::readThread(T& have) {
	if (read == write) {
		return false;
	}
	have = messages[read];
	read = ((read + 1) % 10);
	return true;
}
//template <>
//class RoundThread<VoiceMess> {
//	private:
//		inline static int read = 0;
//		inline static int write = 0;
//		inline static vector<VoiceMess> messages = vector<VoiceMess>(10);
//	public:
//		static bool readThread(VoiceMess& recieve) {
//			if (read == write) { return false; }
//			recieve.dataLength = messages[read].dataLength;
//			recieve.quitTime = messages[read].quitTime;
//			recieve.startBit = messages[read].startBit;
//			recieve.voiceData = messages[read].voiceData;
//			read = ((read + 1) % 10);
//			return true;
//		};
//		static void writeThread(const VoiceMess& voiceMess) {
//			if ((write + 1) % 10 == read) {
//				return;
//			}
//			messages[write] = voiceMess;
//			write = ((write + 1) % 10);
//		}
//};
//
//template <>
//class RoundThread<SendModel> {
//private:
//	inline static int read = 0;
//	inline static int write = 0;
//	inline static vector<SendModel> messages = vector<SendModel>(10);
//public:
//	static void writeThread(const SendModel& voiceMess) {
//		if ((write + 1) % 10 == read) {
//			return;
//		}
//		messages[write] = voiceMess;
//		write = ((write + 1) % 10);
//	}
//	static bool readThread(SendModel& recieve) {
//		if (read == write) { return false; }
//		recieve.img = messages[read].img;
//		recieve.text = messages[read].text;
//		read = ((read + 1) % 10);
//		return true;
//	};
//};
#endif