#include "Audio.h"
#include "AudioVoiceManager.h"
#include "AudioLoader.h"
#include "AudioSwapChain.h"
#include "AudioHelpers.h"
#include "AudioMixer.h"
#define SOKOL_IMPL
#include "sokol_audio.h"

AoedeAudio::AoedeAudio(int numFrames, int channels, int sampleRate)
	: m_numFrames(numFrames)
	, m_channels(channels)
	, m_sampleRate(sampleRate)
{

}

AoedeAudio::~AoedeAudio()
{

}
void audioCallback(float* buffer, int numFrames, int numChannels, void* userData)
{
	//Get our audio data from the passed-in userData variable.
	AudioSwapChain* audioData((AudioSwapChain*)userData);

	//Get the samplerate our soundcard is running at.
	const float samplerate((float)saudio_sample_rate());

	//Just in case...
	if (audioData->isPopulated.load())
	{
		for (int i = 0; i < numFrames; ++i)
		{
			buffer[2 * i + 0] = 0.0f;// left channel
			buffer[2 * i + 1] = 0.0f;


			buffer[2 * i + 0] += audioData->getBuffer()[2 * i];
			buffer[2 * i + 1] += audioData->getBuffer()[2 * i + 1];
		}
		audioData->isPopulated.store(false);
	}
}

void AoedeAudio::init()
{
	m_audioVoiceManager = new AudioVoiceManager();

	bufferPtr = new AudioSwapChain(m_numFrames, m_channels);
	m_audioMixer = std::make_unique<AudioMixer>(m_numFrames, m_channels, m_sampleRate);

	PopulateAudioBuffer();

	saudio_desc audioDescriptor = {};

	audioDescriptor.num_channels = m_channels;
	audioDescriptor.stream_userdata_cb = audioCallback;
	audioDescriptor.sample_rate = m_sampleRate * m_channels;
	audioDescriptor.user_data = (void*)bufferPtr;
	saudio_setup(&audioDescriptor);

	if (!saudio_isvalid())
	{
		exit(0);
	}
}

void AoedeAudio::PopulateAudioBuffer()
{
	m_audioVoiceManager->updateVoices();
	if (!bufferPtr->isPopulated.load())
	{
		bufferPtr->write(m_audioMixer->outputAudio(m_audioVoiceManager->getActiveVoices(), m_audioVoiceManager->getActiveListener()));
		bufferPtr->isPopulated.store(true);
	}
}

void AoedeAudio::playSound(AudioHandle handle)
{
	if (m_audioHandles.find(handle.getName()) != m_audioHandles.end())
	{
		// Handle Name Already exists
	}

	if (AudioLoader::getInstance().GetAudio(handle.getDesc().filename) == nullptr)
	{
		AudioLoader::getInstance().loadAudio(handle.getDesc().filename);
	}

	m_audioHandles.insert({ handle.getName(), handle });

	int numframes = AudioLoader::getInstance().GetAudio(handle.getDesc().filename)->numFrames;
	m_audioVoiceManager->allocateVoice(&m_audioHandles[handle.getName()], numframes);
	m_audioVoiceManager->activateVoice(&m_audioHandles[handle.getName()]);
}

AudioVoiceManager* AoedeAudio::getAudioVoiceManager()
{
	return m_audioVoiceManager;
}

void AoedeAudio::updatePosition(std::string handleName, float x, float y, float z)
{
	if (m_audioHandles.find(handleName) != m_audioHandles.end())
	{
		vec3 newPosition;
		newPosition.x = x;
		newPosition.y = y;
		newPosition.z = z;
		m_audioHandles[handleName].setPosition(newPosition);
	}
}