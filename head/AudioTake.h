#ifndef AUDIO_TAKE_H
#define AUDIO_TAKE_H
#include <portaudio.h>
#include <functional>
#include <vector>
#include <memory>
using std::vector;
using std::function;
typedef struct VoiceMess {
	bool startBit;
	int quitTime;
	vector<float> voiceData;
	int dataLength;
} VoiceMess;
class AudioTake {
	private:
		std::unique_ptr<VoiceMess> voiceMess;
		const static int SAMPLE_RATE = 16000;
		const static unsigned long BUFFER = 256;
		const static int INPUTCHANNEL = 1;
		const static int OUTPUTCHANNEL = 1;
		static int pastCallback(
			const void* input,
			void* output,
			unsigned long frameCount,
			const PaStreamCallbackTimeInfo* timeInfo,
			const PaStreamCallbackFlags status,
			void* userData
			);
		PaStream* stream;
		void initPaStream();
		
	public:
		AudioTake() {
			initPaStream();
		}
		~AudioTake() {
			Pa_StopStream(stream);
			Pa_CloseStream(stream);
			Pa_Terminate();
		}
		bool startStream() { return Pa_StartStream(stream); }
	
};
#endif