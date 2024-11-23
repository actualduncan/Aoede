#pragma once

#include <iostream>
#include "AudioHelpers.h"
#include <map>
class AudioLoader;
class AudioVoiceManager;

class AoedeAudio
{
public:
	AoedeAudio();
	~AoedeAudio();
	void init();
	void playSound(AudioHandle handle);
private:
	std::map<const char*, AudioHandle> m_audioHandles;
	std::unique_ptr<AudioLoader> m_audioLoader;
	std::unique_ptr<AudioVoiceManager> m_audioVoiceManager;
};

