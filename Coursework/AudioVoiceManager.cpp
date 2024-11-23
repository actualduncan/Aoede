#include "AudioVoiceManager.h"

AudioVoiceManager::AudioVoiceManager()
{
	voicePool.reserve(MAX_ALLOCATED_VOICES);
	for (int i = 0; i < MAX_ALLOCATED_VOICES; ++i)
	{
		voicePool.push_back(std::make_unique<AudioVoice>(i));
	}
}

AudioVoiceManager::~AudioVoiceManager()
{

}

bool AudioVoiceManager::allocateVoice(AudioHandle* handle)
{

}