#pragma once
#include "AudioVoice.h"
#include "AudioListener.h"
#include <vector>
#include <iostream>

class AudioVoiceManager
{
public:
	AudioVoiceManager();
	~AudioVoiceManager();

	bool allocateVoice(AudioHandle* handle);
private:
	static constexpr int MAX_ALLOCATED_VOICES = 15;

	std::vector<std::unique_ptr<AudioVoice>> voicePool;

	std::shared_ptr<AudioListener> activeListener;
};

