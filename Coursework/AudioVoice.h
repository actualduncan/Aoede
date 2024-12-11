#pragma once

#include <iostream>
class AudioHandle;
class AudioVoice
{
public:
	AudioVoice(int id);
	~AudioVoice();
	void update(int bufferSize);
	void setAudioHandle(AudioHandle* audioHandle);
	AudioHandle* getAudioHandle();
	bool isActive();
	void setActive(bool active);
	void setAttenuation(float att);
	float getAttenuation();
	void setPan(float left, float right);

	float getPanL();
	float getPanR();
	float getLastPanL();
	float getLastPanR();

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
	float lastPanL;
	float lastPanR;
	float attenuation;

	bool isLooping;
	bool m_isActive;

};

