#include "AudioSwapChain.h"
AudioSwapChain::AudioSwapChain(int bufferSize, int channels) 
	: m_bufferSize(bufferSize)
	, m_channels(channels)
{
	m_buffer = new float[m_bufferSize * m_channels];
	m_buffer2 = new float[m_bufferSize * m_channels];

	for (int i = 0; i < m_bufferSize * m_channels; ++i)
	{
		m_buffer[i] = 0;
		m_buffer2[i] = 0;
	}

	m_currentbuffer = m_buffer;
};

AudioSwapChain::~AudioSwapChain() 
{
	delete[] m_buffer;
	delete[] m_buffer2;
};

void AudioSwapChain::clearBuffer()
{
	for (int i = 0; i <= m_bufferSize * m_channels; ++i)
	{
		m_currentbuffer[i] = 0;
	}
};

float* AudioSwapChain::getBuffer() 
{ 
	return m_currentbuffer;
};

void AudioSwapChain::write(float* data) {
	clearBuffer();
	SwitchBuffer();
	if (m_currentbuffer == m_buffer)
	{
		for (int i = 0; i < m_bufferSize * m_channels; ++i)
		{
			m_buffer2[i] = data[i];
		}
	}
	else
	{
		for (int i = 0; i < m_bufferSize * m_channels; ++i)
		{
			m_buffer[i] = data[i];

		}
	}
};

void AudioSwapChain::SwitchBuffer()
{
	if (m_currentbuffer == m_buffer)
	{
		m_currentbuffer = m_buffer2;
	}
	else
	{
		m_currentbuffer = m_buffer;
	}

}