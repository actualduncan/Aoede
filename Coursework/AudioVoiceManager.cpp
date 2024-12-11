#include "AudioVoiceManager.h"
#include "AudioHelpers.h"
#include <cmath>
#include <iostream>
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
void AudioVoiceManager::setListener(AudioListener* listener)
{
	activeListener = listener;
}

bool AudioVoiceManager::allocateVoice(AudioHandle* handle, int numFrames)
{

	for (auto& it = voicePool.begin(); it < voicePool.end(); ++it)
	{
		if ((*it)->isActive())
		{
			continue;
		}
		(*it)->setAudioHandle(handle);
		(*it)->numFrames = numFrames;
		return true;
	}

	return false;
}

void AudioVoiceManager::activateVoice(AudioHandle* handle)
{
	for (auto& it = voicePool.begin(); it < voicePool.end(); ++it)
	{
		if ((*it)->getAudioHandle() == nullptr)
		{
			continue;
		}

		if ((*it)->getAudioHandle()->getName() == handle->getName())
		{
			(*it)->setActive(true);
		}
	}
}

std::vector<AudioVoice*>* AudioVoiceManager::getActiveVoices()
{
	return &voicePool;
}


AudioListener* AudioVoiceManager::getActiveListener()
{
	return activeListener;
}

void AudioVoiceManager::updateVoices()
{
	for (auto& it = voicePool.begin(); it < voicePool.end(); ++it)
	{
		if ((*it)->isActive())
		{

		}
	}
}

AudioVoice* AudioVoiceManager::getVoice(AudioHandle handle)
{
	for (auto& it = voicePool.begin(); it < voicePool.end(); ++it)
	{
		if ((*it)->getAudioHandle()->getName() == handle.getName())
		{
			return (*it);
		}
	}

	return nullptr;

}
