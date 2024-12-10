#pragma once

#include <iostream>
#include <map>
#include <vector>
#include "AudioLoader.h"
class AudioVoiceManager;

class AudioHandle;
class AudioRingBuffer;
class AoedeAudio
{
public:
	AoedeAudio();
	~AoedeAudio();
	void init();
	void update();
	void updatePosition(std::string, float x, float y, float z);
	void playSound(AudioHandle handle);
	void PopulateAudioBuffer();
	AudioVoiceManager* getAudioVoiceManager();
private:
	std::map<std::string, AudioHandle> m_audioHandles;
	AudioVoiceManager* m_audioVoiceManager;
	std::vector<AudioLoader::AudioData*> data;
	AudioRingBuffer* bufferPtr;
};

