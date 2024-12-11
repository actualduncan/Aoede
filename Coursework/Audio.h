#pragma once

#include <iostream>
#include <map>
#include <vector>

class AudioVoiceManager;
class AudioHandle;
class AudioMixer;
class AudioSwapChain;
class AoedeAudio
{
public:
	AoedeAudio(int numFrames, int channels, int sampleRate);
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

	std::unique_ptr<AudioMixer> m_audioMixer;
	AudioSwapChain* bufferPtr;
	int m_numFrames;
	int m_channels;
	int m_sampleRate;
};

