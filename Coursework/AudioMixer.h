#pragma once
#include <vector>
class AudioLoader;
class AudioVoice;

class AudioMixer
{
public:
	AudioMixer(AudioLoader* audioLoader) : m_audioLoader(audioLoader) {};
	~AudioMixer();
	
	float* outputAudio(std::vector<AudioVoice*> activeVoices);
private:
	struct OutputMixData
	{
		unsigned int channels;
		unsigned int samplerate;
		unsigned int currentFrame = 0;
		unsigned int numFrames;
	};

	AudioLoader* m_audioLoader;
};

