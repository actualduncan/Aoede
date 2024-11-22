#include "AudioLoader.h"
#define DR_MP3_IMPLEMENTATION
#include "dr_mp3.h"
#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"
AudioLoader::AudioLoader()
{

}

AudioLoader::~AudioLoader()
{

}

bool AudioLoader::loadMP3(const char* filename)
{
	AudioData audioData;
	drmp3_config config;

	audioData.filename = filename;

	audioData.data = drmp3_open_file_and_read_pcm_frames_f32(audioData.filename,
		&config,
		&audioData.numFrames,
		NULL);

	audioData.samplerate = config.sampleRate;
	audioData.channels = config.channels;

	loadedAudio.insert({ audioData.filename, audioData });

	convertMonoToStereo(filename);
	return true;
}

bool AudioLoader::loadWAV(const char* filename)
{
	AudioData audioData;

	audioData.filename = filename;

	audioData.data = drwav_open_file_and_read_pcm_frames_f32(audioData.filename,
		&audioData.channels,
		&audioData.samplerate,
		&audioData.numFrames,
		NULL);

	loadedAudio.insert({ audioData.filename, audioData });

	convertMonoToStereo(filename);
	return true;
}

bool AudioLoader::convertMonoToStereo(const char* filename)
{
	if (loadedAudio.find(filename) != loadedAudio.end())
	{
		AudioData& audioData = loadedAudio[filename];

		if (audioData.channels == 2)
		{
			return true;
		}

		float* oldData = audioData.data;
		float* newData = new float[audioData.numFrames * 2];

		for (int i = 0; i < audioData.numFrames; ++i)
		{
			newData[2 * i + 0] = oldData[i];
			newData[2 * i + 1] = oldData[i];
		}

		delete[] oldData;
		audioData.data = newData;

		audioData.numFrames *= 2;
		audioData.channels = 2;
		return true;
	}

	return false;
}

AudioLoader::AudioData* AudioLoader::GetAudio(const char* filename)
{
	if (loadedAudio.find(filename) != loadedAudio.end())
	{
		return &loadedAudio[filename];
	}
	else
	{
		return nullptr;
	}
}

