#pragma once

#include "AudioListener.h"
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

	bool allocateVoice(AudioHandle* handle, int numFrames);
	void activateVoice(AudioHandle* handle);
	std::vector<AudioVoice*>* getActiveVoices();
	void setListener(AudioListener* listener);
	void updateVoices();
	AudioVoice* getVoice(AudioHandle handle);
private:
	static constexpr int MAX_ALLOCATED_VOICES = 15;

	std::vector<AudioVoice*> voicePool;

	AudioListener* activeListener;

	int x, y, z;

	int activeVoices;
};

