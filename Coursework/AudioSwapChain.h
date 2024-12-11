#pragma once
#include <atomic>
class AudioSwapChain
{
public:
	AudioSwapChain(int bufferSize, int channels);
	~AudioSwapChain();

	void clearBuffer();
	float* getBuffer();
	void write( float* data);
	void SwitchBuffer();

	std::atomic<bool> isPopulated = false;
private:
	int m_bufferSize;
	int m_channels;
	std::atomic<float*> m_currentbuffer;
	float* m_buffer;
	float* m_buffer2;
};

