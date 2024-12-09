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
	else if (value >= max)
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

void panAudio(float angle, float& left, float& right)

{
	left = (std::sqrtf(2) / 2.0f) * (std::cosf(angle) + sinf(angle));
	right = (std::sqrtf(2) / 2.0f) * (std::cosf(angle) - sinf(angle));

	if (std::abs(std::abs(left) - std::abs(right)) < 0.2f)
	{
		right = -left;
	}
}

float getAngle(vec3 forward, vec3 pos1, vec3 pos2)
{
	vec3 direction;
	direction.x = pos1.x - pos2.x;
	direction.y = pos1.y - pos2.y;
	direction.z = pos1.z - pos2.z;

	float mag = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2) + std::pow(direction.z, 2));
	direction.x /= mag;
	direction.y /= mag;
	direction.z /= mag;
	float dot = direction.x * forward.x  + direction.y * forward.y + direction.z * forward.z;


	return std::acos(dot);

}

void AudioVoiceManager::updateVoices()
{
	for (auto& it = voicePool.begin(); it < voicePool.end(); ++it)
	{
		if ((*it)->isActive())
		{
			//figure out 
			(*it)->setAttenuation(lerp(0.7f, 0.0f, ramp(1.0f, 20.0f, getDistance(activeListener->getPosition(), (*it)->getAudioHandle()->getPosition()))));
			float panL = 0.0f;
			float panR = 0.0f;
			float angle = getAngle(activeListener->getRotation(), activeListener->getPosition(), (*it)->getAudioHandle()->getPosition());

			panAudio(angle, panL, panR);
			(*it)->setPan(panL, panR);

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
	
}
