#pragma once

#include "dr_wav.h"
#include "AudioHelpers.h"

#include "dr_mp3.h"
#include <map>



class AudioLoader
{
public:

	struct AudioData
	{
		unsigned int channels;
		unsigned int samplerate;
		drwav_uint64 currentFrame = 0;
		drwav_uint64 numFrames;
		const char* filename;
		float* data;
	};

	AudioLoader();
	~AudioLoader();

	bool loadAudio(const char* filename);
	bool loadWAV(const char* filename);
	bool loadMP3(const char* filename);
	bool convertMonoToStereo(const char* filename);
	AudioData* GetAudio(const char* filename);

private:
	std::map<const char*, AudioData> loadedAudio;
};

