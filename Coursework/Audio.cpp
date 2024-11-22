#include "Audio.h"
#include "AudioLoader.h"

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
	AudioLoader::AudioData* audioData((AudioLoader::AudioData*)userData);

	//Get the samplerate our soundcard is running at.
	const float samplerate((float)saudio_sample_rate());

	//Just in case...
	if (audioData)
	{
		for (int i = 0; i < numFrames; ++i)
		{
			buffer[2 * i + 0] = 0.0f;// left channel
			buffer[2 * i + 1] = 0.0f;
			buffer[2 * i + 0] = audioData->data[audioData->currentFrame];
			buffer[2 * i + 1] = audioData->data[audioData->currentFrame + 1];

			audioData->currentFrame = ((audioData->currentFrame + 1) % audioData->numFrames);

		}
	}
}

void AoedeAudio::init()
{
	audioLoader = std::make_unique<AudioLoader>();
	if (audioLoader->loadWAV("res/loop.wav"))
	{
		AudioLoader::AudioData& audioData = *audioLoader->GetAudio("res/loop.wav");

		saudio_desc audioDescriptor = {};

		audioDescriptor.num_channels = 2;
		audioDescriptor.stream_userdata_cb = audioCallback;
		audioDescriptor.sample_rate = audioData.samplerate * 2;
		//audioDescriptor.buffer_frames = 1;
		audioDescriptor.user_data = (void*)&audioData;

		saudio_setup(&audioDescriptor);

	}
	
	if (!saudio_isvalid())
	{
		exit(0);
	}
}

