#pragma once
#include "AudioHelpers.h"
#include <iostream>
class AudioVoice
{
public:
	AudioVoice(int id) : id(id) { m_audioHandle = nullptr; };
	~AudioVoice() {};
	void update(int bufferSize);
	void setAudioHandle(AudioHandle* audioHandle) { m_audioHandle = audioHandle;  };
	AudioHandle* getAudioHandle() { return m_audioHandle; };
	bool isActive() { return m_isActive; };
	void setActive(bool active) { m_isActive = active; };
	void setAttenuation(float att)
	{
		attenuation = att;
	};
	float getAttenuation() { return attenuation; };
	void setPan(float left, float right) { 
		panL = left;
		panR = right;
	};

	float getPanL() { return panL; };
	float getPanR() { return panR; };
	bool populated;
	int currentFrame = 0;
	int numFrames;
private:
	AudioHandle* m_audioHandle;
	int id;
	int priority;

	float durationSeconds;
	float volume;
	float pitch;
	float panL;
	float panR;
	float attenuation;
	bool isLooping;
	bool m_isActive;

};

