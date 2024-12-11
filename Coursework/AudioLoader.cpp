#include "AudioLoader.h"
#include <vector>
#define DR_MP3_IMPLEMENTATION
#include "dr_mp3.h"
#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"
#include <string>
namespace AudioFileType
{
	const char* WAV = ".wav";
	const char* MP3 = ".mp3";

};
AudioLoader::AudioLoader()
{

}

AudioLoader::~AudioLoader()
{

}

bool whitepsace(char c)
{
	return c == ' ';
}

bool AudioLoader::loadAudio(const char* filename)
{
	std::string filenameAsString(filename);

	std::string filepath = filenameAsString.substr(filenameAsString.find('.'));

	if (filepath == AudioFileType::WAV)
	{
		return loadWAV(filename);
	}
	else if (filepath == AudioFileType::MP3)
	{
		return loadMP3(filename);
	}
	else
	{
		// incorrect input path
		return false;
	}
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
	audioData.numFrames *= config.channels;
	audioData.samplerate = config.sampleRate;
	audioData.channels = config.channels;
	m_loadedAudio.insert({ audioData.filename, audioData });

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

	m_loadedAudio.insert({ audioData.filename, audioData });

	convertMonoToStereo(filename);
	return true;
}

bool AudioLoader::convertMonoToStereo(const char* filename)
{
	if (m_loadedAudio.find(filename) != m_loadedAudio.end())
	{
		AudioData& audioData = m_loadedAudio[filename];

		if (audioData.channels == 2)
		{
			return true;
		}

		float* oldData = audioData.data;
		float* newData = new float[audioData.numFrames * 2];
		std::vector<float> rawr;
		for (int i = 0; i < audioData.numFrames; ++i)
		{
			newData[2 * i + 0] = oldData[i];
			newData[2 * i + 1] = oldData[i];
			rawr.push_back(newData[2 * i + 0]);
			rawr.push_back(newData[2 * i + 1]);
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
	if (m_loadedAudio.find(filename) != m_loadedAudio.end())
	{
		return &m_loadedAudio[filename];
	}
	else
	{
		return nullptr;
	}
}

float* AudioLoader::GetAudioFromFrame(const char* filename, int size, int marker)
{
	if (m_loadedAudio.find(filename) != m_loadedAudio.end())
	{
		return &loadedAudio[filename].data[marker % loadedAudio[filename].numFrames];
	}
}
