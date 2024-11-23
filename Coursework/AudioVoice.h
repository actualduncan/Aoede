#pragma once
#include "AudioLoader.h"
#include <iostream>
class AudioVoice
{
public:
	AudioVoice(int id) : id(id) {};
	~AudioVoice() {};
	bool SetAudioAsset(std::shared_ptr<AudioLoader::AudioData> inAudioAsset) {};
private:
	std::shared_ptr<AudioLoader::AudioData> audioAsset;

	int id;
	int priority;
	float durationSeconds;
	float volume;
	float pitch;
	float pan;
	float attenuation;
	bool isLooping;
	bool isActive;

};

