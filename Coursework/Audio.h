#pragma once

#include <iostream>
#include <map>
#include <vector>
#include "AudioLoader.h"
class AudioVoiceManager;

class AudioHandle;

class AoedeAudio
{
public:
	AoedeAudio();
	~AoedeAudio();
	void init();
	void update();
	void playSound(AudioHandle handle);
	void PopulateAudioBuffer();
private:
	std::map<const char*, AudioHandle> m_audioHandles;
	std::unique_ptr<AudioLoader> m_audioLoader;
	std::unique_ptr<AudioVoiceManager> m_audioVoiceManager;
	std::vector<AudioLoader::AudioData*> data;
};

