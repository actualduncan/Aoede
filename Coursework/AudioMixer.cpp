#include "AudioMixer.h"
#include "AudioLoader.h"
#include "AudioListener.h"
#include "AudioVoice.h"
#include "AudioHelpers.h"
#include <cmath>

namespace MathHelpers
{
	float getDistance(vec3 position1, vec3 position2)
	{
		return std::abs(std::sqrtf(std::powf((position1.x - position2.x), 2) + std::powf((position1.y - position2.y), 2) + std::powf((position1.z - position2.z), 2)));
	}

	const float M_PI = 3.14f;

	float getAngle(vec3 forward, vec3 pos1, vec3 pos2, vec3 right)

	{
		vec3 direction;
		direction.x = pos1.x - pos2.x;
		direction.y = pos1.y - pos2.y;
		direction.z = pos1.z - pos2.z;

		float mag = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2) + std::pow(direction.z, 2));
		if (mag == 0)
		{
			return 0.0f;
		}
		direction.x /= mag;
		direction.y /= mag;
		direction.z /= mag;

		float dotForward = forward.x * direction.x + forward.z * direction.z;
		float dotRight = right.x * direction.x + right.z * direction.z;
		float angle = std::atan2(dotRight, dotForward);

		// Wrap the angle to the range
		if (angle > M_PI)
			angle -= 2.0f * M_PI;
		else if (angle < -M_PI)
			angle += 2.0f * M_PI;

		return angle;


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
};

AudioMixer::AudioMixer(int maxBufferSize, int channels, int sampleRate)
	: m_maxBufferSize(maxBufferSize)
	, m_channels(channels)
	, m_sampleRate(sampleRate)
{
	m_audioMix = new float[m_maxBufferSize * channels];
	resetMix();
}

AudioMixer::~AudioMixer()
{
	delete[] m_audioMix;
}
void AudioMixer::resetMix()
{
	for (int i = 0; i <= m_maxBufferSize; ++i)
	{
		// left
		m_audioMix[2 * i + 0] = 0.0f;
		m_audioMix[2 * i + 1] = 0.0f;
	}
}

float* AudioMixer::outputAudio(std::vector<AudioVoice*>* activeVoices, AudioListener* activeListener)
{
	resetMix();
	for (auto& activeVoiceIt = activeVoices->begin(); activeVoiceIt < activeVoices->end(); ++activeVoiceIt)
	{
		if ((*activeVoiceIt)->isActive())
{
			Mix(AudioLoader::getInstance().GetAudioFromFrame((*activeVoiceIt)->getAudioHandle()->getDesc().filename, 0, (*activeVoiceIt)->currentFrame),
				*activeVoiceIt, activeListener);

			if ((*activeVoiceIt)->getAudioHandle()->getDesc().isLooping)
	{
				(*activeVoiceIt)->currentFrame = ((*activeVoiceIt)->currentFrame + m_maxBufferSize) % (*activeVoiceIt)->numFrames;
			}
			else
			{
				(*activeVoiceIt)->currentFrame += m_maxBufferSize;
			}

		}


    	if ((*activeVoiceIt)->currentFrame > (*activeVoiceIt)->numFrames && !(*activeVoiceIt)->getAudioHandle()->getDesc().isLooping)
		{
			(*activeVoiceIt)->setActive(false);
			(*activeVoiceIt)->currentFrame = 0;
		}
	}
	normalizeMix();
	return m_audioMix;
}

void AudioMixer::panAudio(float angle, float& left, float& right)
{
	// For sounds behind the listener (angle near  balance left and right
	if (std::abs(angle - MathHelpers::M_PI) < 0.1f || std::abs(angle + MathHelpers::M_PI) < 0.1f)
	{
		left = right = 0.5f; // Equal volume for both channels
	}
	else
	{
		// Default stereo panning
		left = (std::sqrtf(2) / 2.0f) * (std::cosf(angle) - sinf(angle));
		right = (std::sqrtf(2) / 2.0f) * (std::cosf(angle) + sinf(angle));
	}
}

void AudioMixer::Mix(float* dataToMix, AudioVoice* voice, AudioListener* activeListener)
{
	int framesLeft = m_maxBufferSize % (voice->numFrames - voice->currentFrame);

	float panL = 0.0f;
	float panR = 0.0f;
	float attenuation = 0.0f;

	float angle = MathHelpers::getAngle(activeListener->getRotation(), activeListener->getPosition(), voice->getAudioHandle()->getPosition(), activeListener->getRight());

	panAudio(angle, panL, panR);
	panL = MathHelpers::lerp(voice->getLastPanL(), panL, 0.15f);
	panR = MathHelpers::lerp(voice->getLastPanR(), panR, 0.15f);
	attenuation = MathHelpers::lerp(0.9f, 0.0f, MathHelpers::ramp(1.0f, 20.0f, MathHelpers::getDistance(activeListener->getPosition(), voice->getAudioHandle()->getPosition())));
	voice->setPan(panL, panR);
	voice->setAttenuation(attenuation);

	for (int i = 0; i < framesLeft; ++i)
	{


		m_audioMix[2 * i + 0] += dataToMix[i + 0] * voice->getAttenuation() * voice->getPanL();
		m_audioMix[2 * i + 1] += dataToMix[i + 1] * voice->getAttenuation() * voice->getPanR();



	}

}


void AudioMixer::normalizeMix()
{
	float maxAmplitude = 0.0f;
	for (int i = 0; i < m_maxBufferSize * 2; ++i) 
	{ 
		maxAmplitude = std::max(maxAmplitude, std::abs(m_audioMix[i]));
	}


	if (maxAmplitude > MAX_AMPLITUDE) 
	{
		float normalizationFactor = MAX_AMPLITUDE / maxAmplitude;

		for (int i = 0; i < m_maxBufferSize * 2; ++i) 
		{ 
			m_audioMix[i] *= normalizationFactor;
		}
	}
}
