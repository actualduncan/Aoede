#pragma once
#include "AudioVoice.h"
#include <vector>
#include <iostream>
#include "AudioListener.h"
class AudioVoiceManager
{
public:
	AudioVoiceManager();
	~AudioVoiceManager();
private:
	static constexpr int MAX_ALLOCATED_VOICES = 15;

	std::vector<std::unique_ptr<AudioVoice>> voicePool;

	std::shared_ptr<AudioListener> activeListener;
};

