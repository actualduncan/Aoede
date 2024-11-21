#pragma once

struct AudioData
{
	unsigned int channels;
	unsigned int samplerate;
	drwav_uint64 currentFrame = 0;
	drwav_uint64 numFrames;
	const char* filename;
	float* data;
};
class AoedeAudio
{
public:
	AoedeAudio();
	~AoedeAudio();
	void init();
private:
	AudioData audioData;
};

