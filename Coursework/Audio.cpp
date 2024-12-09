#include "Audio.h"
#include "AudioVoiceManager.h"
#include "AudioLoader.h"
#include "AudioRingBuffer.h"
#include "AudioHelpers.h"
#define SOKOL_IMPL
#include "sokol_audio.h"

AoedeAudio::AoedeAudio()
{

}

AoedeAudio::~AoedeAudio()
{

}
void audioCallback(float* buffer, int numFrames, int numChannels, void* userData)
{
	//Get our audio data from the passed-in userData variable.
	AudioRingBuffer* audioData((AudioRingBuffer*)userData);

	//Get the samplerate our soundcard is running at.
	const float samplerate((float)saudio_sample_rate());

	//Just in case...
	if (audioData->isPopulated)
	{
		audioData->isAvailable = false;

		//memcpy(buffer, audioData->getBuffer(), numFrames*2);
		for (int i = 0; i < numFrames; ++i)
		{
			buffer[2 * i + 0] = 0.0f;// left channel
			buffer[2 * i + 1] = 0.0f;


			buffer[2 * i + 0] += audioData->getBuffer()[2 * i];
			buffer[2 * i + 1] += audioData->getBuffer()[2 * i+1];

		}


		audioData->clearBuffer();

		audioData->SwitchBuffer();
		audioData->isAvailable = true;
	}
}

void AoedeAudio::init()
{
	m_audioLoader = std::make_unique<AudioLoader>();
	m_audioVoiceManager = new AudioVoiceManager();
	bufferPtr = new AudioRingBuffer();

	PopulateAudioBuffer();

	saudio_desc audioDescriptor = {};

	audioDescriptor.num_channels = 2;
	audioDescriptor.stream_userdata_cb = audioCallback;
	audioDescriptor.sample_rate = 44100 *2;
		//audioDescriptor.buffer_frames = 1;
	audioDescriptor.user_data = (void*)bufferPtr;
	
	saudio_setup(&audioDescriptor);
	
	if (!saudio_isvalid())
	{
		exit(0);
	}
}

void processAudio(float* audio, int numframes, float att, float leftpan, float rightpan)

{
	for (int i = 0; i < numframes; ++i)
	{
		audio[2 * i + 0] *= leftpan;
		audio[2 * i + 1] *= rightpan;
	}
}

void AoedeAudio::PopulateAudioBuffer()
{
	m_audioVoiceManager->updateVoices();
	std::vector<AudioVoice*>* voices = m_audioVoiceManager->getActiveVoices();
	
	for (auto& it = voices->begin(); it < voices->end(); ++it)
	{
		if ((*it)->isActive() && (*it)->currentFrame < (*it)->numFrames && !bufferPtr->isPopulated)
		{

			bufferPtr->write(2048 % ((*it)->numFrames - (*it)->currentFrame), m_audioLoader->GetAudio((*it)->getAudioHandle()->getDesc().filename)->data, (*it)->currentFrame, (*it)->getAttenuation(), (*it)->getPanL(), (*it)->getPanR());
			(*it)->currentFrame += 2048;
		}

		if ((*it)->isActive() && (*it)->currentFrame > (*it)->numFrames)
		{
			(*it)->setActive(false);
			(*it)->currentFrame = 0;
		}
	}

	bufferPtr->isPopulated = true;

	
}

void AoedeAudio::playSound(AudioHandle handle)
{
	if (m_audioHandles.find(handle.getName()) != m_audioHandles.end())
	{
		// Handle Name Already exists
	}

	if (m_audioLoader->GetAudio(handle.getDesc().filename) == nullptr)
	{
		m_audioLoader->loadAudio(handle.getDesc().filename);
	}

	m_audioHandles.insert({ handle.getName(), handle });

	int numframes = m_audioLoader->GetAudio(handle.getDesc().filename)->numFrames;
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