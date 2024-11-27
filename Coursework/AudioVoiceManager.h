#pragma once

//#include "AudioListener.h"
#include <vector>
#include <iostream>
#include "AudioVoice.h"
class AudioVoice;
class AudioHandle;

class AudioVoiceManager
{
public:
	AudioVoiceManager();
	~AudioVoiceManager();

	bool allocateVoice(AudioHandle* handle);
	void activateVoice(AudioHandle* handle);
	std::vector<AudioVoice*>* getActiveVoices();
private:
	static constexpr int MAX_ALLOCATED_VOICES = 15;

	std::vector<AudioVoice*> voicePool;

	//std::shared_ptr<AudioListener> activeListener;

	int activeVoices;
};

