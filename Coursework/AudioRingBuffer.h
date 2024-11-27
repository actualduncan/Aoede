#pragma once
class AudioRingBuffer
{
public:
	AudioRingBuffer(static int size);
	~AudioRingBuffer();
private:
	float* buffer;
};

