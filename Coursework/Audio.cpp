#include "Audio.h"
#include "AudioVoiceManager.h"
#include "AudioLoader.h"
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
	std::vector<AudioLoader::AudioData*>* audioData((std::vector<AudioLoader::AudioData*>*)userData);

	//Get the samplerate our soundcard is running at.
	const float samplerate((float)saudio_sample_rate());

	//Just in case...
	if (audioData)
	{
		for (int i = 0; i < numFrames; ++i)
		{
			buffer[2 * i + 0] = 0.0f;// left channel
			buffer[2 * i + 1] = 0.0f;
			for (auto& it = audioData->begin(); it < audioData->end(); ++it)
			{

				buffer[2 * i + 0] += (*it)->data[(*it)->currentFrame];
				buffer[2 * i + 1] += (*it)->data[(*it)->currentFrame + 1];

				(*it)->currentFrame = (((*it)->currentFrame + 1) % (*it)->numFrames);
			}
		}
	}
}


void AoedeAudio::init()
{
	m_audioLoader = std::make_unique<AudioLoader>();
	m_audioVoiceManager = std::make_unique<AudioVoiceManager>();

	AudioDesc desc{};
	desc.filename = "res/woo.mp3";
	AudioHandle handle("yes", desc);

	AudioDesc desc2{};
	desc2.filename = "res/Loop.wav";

	AudioHandle handle2("woop", desc2);

	playSound(handle);
	playSound(handle2);

	PopulateAudioBuffer()
		;
	saudio_desc audioDescriptor = {};

	audioDescriptor.num_channels = 2;
	audioDescriptor.stream_userdata_cb = audioCallback;
	audioDescriptor.sample_rate = data[0]->samplerate * 2;
		//audioDescriptor.buffer_frames = 1;
	audioDescriptor.user_data = (void*)&data;

	saudio_setup(&audioDescriptor);


	
	if (!saudio_isvalid())
	{
		exit(0);
	}
}

void AoedeAudio::PopulateAudioBuffer()
{
	std::vector<AudioVoice*>* voices = m_audioVoiceManager->getActiveVoices();
	for (auto& it = voices->begin(); it < voices->end(); ++it)
	{
		if ((*it)->isActive())
		{
			data.push_back(m_audioLoader->GetAudio((*it)->getAudioHandle()->getDesc().filename));
		}

	}
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

	m_audioVoiceManager->allocateVoice(&m_audioHandles[handle.getName()]);
	m_audioVoiceManager->activateVoice(&m_audioHandles[handle.getName()]);

	// i don't need audio mixer
	// get buffer size, add audio data to buffer then use callback to make audio go in ears, all this mixer shite is bad
	// RINGBUFFER!"

	
}