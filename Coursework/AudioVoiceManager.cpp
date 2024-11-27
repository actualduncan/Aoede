#include "AudioVoiceManager.h"
#include "AudioHelpers.h"
AudioVoiceManager::AudioVoiceManager()
{
	voicePool.reserve(MAX_ALLOCATED_VOICES);
	for (int i = 0; i < MAX_ALLOCATED_VOICES; ++i)
	{
		voicePool.push_back(new AudioVoice(i));
	}
}

AudioVoiceManager::~AudioVoiceManager()
{

}

bool AudioVoiceManager::allocateVoice(AudioHandle* handle)
{

	for (auto& it = voicePool.begin(); it < voicePool.end(); ++it)
	{
		if ((*it)->isActive())
		{
			continue;
		}
		(*it)->setAudioHandle(handle);
		return true;
	}

	return false;
}

void AudioVoiceManager::activateVoice(AudioHandle* handle)
{
	for (auto& it = voicePool.begin(); it < voicePool.end(); ++it)
	{
		if ((*it)->getAudioHandle()->getName() == handle->getName() )
		{
			(*it)->setActive(true);
			return;
		}
	}
}

std::vector<AudioVoice*>* AudioVoiceManager::getActiveVoices()
{
	return &voicePool;
}