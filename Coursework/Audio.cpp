#include "Audio.h"

#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

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
	AudioData* audioData((AudioData*)userData);

	//Get the samplerate our soundcard is running at.
	const float samplerate((float)saudio_sample_rate());



	//Just in case...
	if (audioData)
	{
		for (int i = 0; i < numFrames; ++i)
		{
			buffer[i] = 0.0f;

			buffer[i] = audioData->data[audioData->currentFrame];
			audioData->currentFrame = (audioData->currentFrame + 1) % audioData->numFrames;

		}
	}
}
AudioData audioData;
void AoedeAudio::init()
{
	audioData.filename = "res/Loop.wav";
	audioData.data = drwav_open_file_and_read_pcm_frames_f32(audioData.filename,
		&audioData.channels,	
		&audioData.samplerate,	
		&audioData.numFrames,	
		NULL);

	saudio_desc audioDescriptor = {};

	audioDescriptor.num_channels = 1;
	audioDescriptor.stream_userdata_cb = audioCallback;
	audioDescriptor.user_data = (void*)&audioData;

	saudio_setup(&audioDescriptor);

	if (!saudio_isvalid())
	{
		exit(0);
	}
}

