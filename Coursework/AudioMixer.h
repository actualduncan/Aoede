#pragma once
#include <vector>
class AudioLoader;
class AudioVoice;

class AudioMixer
{
public:
	AudioMixer(AudioLoader* audioLoader, int maxBufferSize);
	~AudioMixer();
	
	float* outputAudio(std::vector<AudioVoice*>* activeVoices);
private:
	float calculateAttenuation();
	void resetMix();
	int m_maxBufferSize;
	float* m_audioMix;
	AudioLoader* m_audioLoader;
};


