#include <iostream>
#include "AudioTake.h"
#include "AudioTranslate.h"
#include "Send.h"
#include "Viewer.h"
#include <windows.h>
int main() {

	SetConsoleOutputCP(CP_UTF8);
	AudioTake audioTake;
	AudioTranslate audioTranslate("../Resources/ggml-small.bin");
	Viewer viewer;
	Send send;
	audioTake.startStream();
	audioTranslate.start();
	viewer.start();
	send.start();

}