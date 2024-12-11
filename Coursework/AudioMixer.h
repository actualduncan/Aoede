#pragma once
#include <vector>
class AudioLoader;
class AudioVoice;
class AudioListener;
class AudioMixer
{
public:
	AudioMixer(int maxBufferSize, int channels, int sampleRate);
	~AudioMixer();
	
	float* outputAudio(std::vector<AudioVoice*>* activeVoices, AudioListener* activeListener);
private:
	float calculateAttenuation();
	void panAudio(float angle, float& left, float& right);
	void resetMix();
	void Mix(float* dataToMix, AudioVoice* voice, AudioListener* activeListener);
	void normalizeMix();
	float* m_audioMix;
	int m_maxBufferSize;
	int m_channels;
	int m_sampleRate;

	// leaving some headroom
	const float MAX_AMPLITUDE = 0.8f;
};


