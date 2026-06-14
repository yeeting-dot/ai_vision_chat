#include "AudioTake.h"
#include "RoundThread.h"
#include <iostream>
#include <memory>
#include <portaudio.h>
#include <chrono>
#include <vector>
#include <cstdlib>
using std::vector;

int AudioTake::pastCallback(
	const void* input,
	void* output,
	unsigned long frameCount,
	const PaStreamCallbackTimeInfo* timeInfo,
	const PaStreamCallbackFlags status,
	void* userData
) {
	VoiceMess* mess = (VoiceMess*)userData;
	float* inputFloat = (float*)input;
	float* outputFloat = (float*)output;
	float average = 0.0;
	//std::cout << "mess length: " << mess->dataLength << std::endl;


	//std::cout << "quitTime: " << mess->quitTime << std::endl;
	//std::cout << "startBit: " << mess->startBit << std::endl;
	//std::cout << "dataLength: " << mess->dataLength << std::endl;
	if (mess->startBit == 1 && mess->quitTime > 2000) {
		//语音翻译
		//std::cout << "mess length: " << mess->dataLength << std::endl;
		std::cout << "To write thread" << std::endl;
		RoundThread<VoiceMess>::writeThread(*mess);
		mess->startBit = 0;
		mess->dataLength = 0;
	}
	for (unsigned long i = mess->dataLength; i < mess->dataLength + frameCount; i++) {
		float data = inputFloat[i - mess->dataLength];
		mess->voiceData[i] = data;
		average += abs(data);
	}
	average /= frameCount;
	//std::cout << "average voice: " << average << std::endl;
	float duration =1000 * (float)frameCount / SAMPLE_RATE;
	if (mess->startBit == 0) mess->startBit = (average < 0.01) ? 0 : 1;
	if (average < 0.01) { mess->quitTime += duration; }
	else { mess->dataLength += frameCount; mess->quitTime = 0; }
	return paContinue;
}

void AudioTake::initPaStream() {
	voiceMess = std::unique_ptr<VoiceMess>(new VoiceMess()
	);
	voiceMess->voiceData = vector<float>(960000);
	voiceMess->dataLength = 0;
	voiceMess->startBit = 0;
	voiceMess->quitTime = 0;
	auto err = Pa_Initialize();
	if (err != paNoError) {
		std::cerr << Pa_GetErrorText(err) << std::endl;
		Pa_CloseStream(stream);
		Pa_Terminate();
		exit(EXIT_FAILURE);
	}
	err = Pa_OpenDefaultStream(
		&stream,
		INPUTCHANNEL, 
		OUTPUTCHANNEL,
		paFloat32,
		SAMPLE_RATE,
		BUFFER,
		pastCallback,
		voiceMess.get()
	);
	if (err != paNoError) {
		std::cerr << Pa_GetErrorText(err) << std::endl;
		Pa_CloseStream(stream);
		exit(EXIT_FAILURE);
	}
	
}