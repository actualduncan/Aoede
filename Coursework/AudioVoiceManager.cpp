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
		if((*it)->getAudioHandle() == nullptr)
		{
			continue;
		}

		if ((*it)->getAudioHandle()->getName() == handle->getName() )
		{
			(*it)->setActive(true);
		}
	}
}

std::vector<AudioVoice*>* AudioVoiceManager::getActiveVoices()
{
	return &voicePool;
}

double lerp(double a, double b, double t)
{
	return a * (1.0 - t) + (b * t);
}



float ramp(float min, float max, float value)
{
	if (value < min)
	{
		return 0.0f;
	}
	else if(value >= max)
	{
		return 1.0f;
	}
	else
	{
		// handle scalar between 0.0f and 1.0f
		return (value - min) / (max - min);

	}
}

float getDistance(vec3 position1, vec3 position2)
{

	return std::abs(std::sqrtf(std::powf((position1.x - position2.x), 2) + std::powf((position1.y - position2.y), 2) + std::powf((position1.z - position2.z), 2)));
}

void AudioVoiceManager::updateVoices()
{
	for (auto& it = voicePool.begin(); it < voicePool.end(); ++it)
	{
		if ((*it)->isActive())
		{
			//figure out 
			(*it)->setAttenuation(lerp(0.7f, 0.0f, ramp(5.0f, 20.0f,getDistance(activeListener->getPosition(), (*it)->getAudioHandle()->getPosition()))));
			
		}
	}

	
}

AudioVoice* AudioVoiceManager::getVoice(AudioHandle handle)
{
	for (auto& it = voicePool.begin(); it < voicePool.end(); ++it)
	{
		if ((*it)->getAudioHandle()->getName() == handle.getName())
		{
			//figure out 
			return (*it);

		}
		}
	
}
