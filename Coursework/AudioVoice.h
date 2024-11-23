#pragma once
#include "AudioHelpers.h"
#include "AudioLoader.h"
#include <iostream>
class AudioVoice
{
public:
	AudioVoice(int id) : id(id) {};
	~AudioVoice() {};
	bool SetAudioAsset(std::shared_ptr<AudioLoader::AudioData> inAudioAsset) {};
	bool isActive() { return m_isActive; };
private:

	int id;
	int priority;
	float durationSeconds;
	float volume;
	float pitch;
	float pan;
	float attenuation;
	bool isLooping;
	bool m_isActive;

};

