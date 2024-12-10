#include "AudioMixer.h"
#include "AudioLoader.h"
#include "AudioVoice.h"

AudioMixer::AudioMixer(AudioLoader* audioLoader, int maxBufferSize) 
	: m_audioLoader(audioLoader)
	, m_maxBufferSize(maxBufferSize)
{
	m_audioMix = new float[m_maxBufferSize];
	resetMix();
}

AudioMixer::~AudioMixer()
{
	delete[] m_audioMix;
}
void AudioMixer::resetMix()
{
	for (int i = 0; i < m_maxBufferSize; ++i)
	{
		m_audioMix[i] = 0.0f;
	}
}

float* AudioMixer::outputAudio(std::vector<AudioVoice*>* activeVoices)
{
	for (auto& it = activeVoices->begin(); it < activeVoices->end(); ++it)
	{

		if ((*it)->isActive() && (*it)->currentFrame > (*it)->numFrames)
		{
			(*it)->setActive(false);
			(*it)->currentFrame = 0;
		}
	}
	return m_audioMix;
}