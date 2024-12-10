#pragma once

#include "dr_wav.h"


#include "dr_mp3.h"
#include <map>



class AudioLoader
{
private:
	AudioLoader();
	~AudioLoader();
public:
	static AudioLoader& getInstance()
	{
		static AudioLoader instance;
		return instance;
	}

	struct AudioData
	{
		unsigned int channels = 2;
		unsigned int samplerate = 44100;
		drwav_uint64 currentFrame = 0;
		drwav_uint64 numFrames = 0;
		const char* filename = "";
		int max_voices = 2;
		float* data;
	};
	


	bool loadAudio(const char* filename);
	bool loadWAV(const char* filename);
	bool loadMP3(const char* filename);
	bool convertMonoToStereo(const char* filename);
	AudioData* GetAudio(const char* filename);
	float* GetAudioFromFrame(const char* filename, int size, int marker);

private:
	std::map<const char*, AudioData> m_loadedAudio;
};

