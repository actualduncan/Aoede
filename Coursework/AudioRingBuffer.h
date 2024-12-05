#pragma once
class AudioRingBuffer
{
public:
	AudioRingBuffer() {
		for (int i = 0; i < bufferSize; ++i)
		{
			buffer[i] = 0;
			buffer2[i] = 0;
		}
		isAvailable = true;
		currentbuffer = buffer;
	};
	~AudioRingBuffer() {};
	void clearBuffer()
	{
		for (int i = 0; i < bufferSize; ++i)
		{
			currentbuffer[i] = 0;
		}

		//isAvailable = true;
	};
	float* getBuffer() { return currentbuffer; };
	void write(int bytes, float* data, int currentFrame) { 

		if (currentbuffer == buffer)
		{
			for (int i = 0; i < bytes; ++i)
			{
				buffer2[i % bufferSize] += data[currentFrame + i];
			}
		}
		else
		{
			for (int i = 0; i < bytes; ++i)
			{
				buffer[i % bufferSize] += data[currentFrame + i];
			}
		}		
	};

	void SwitchBuffer()
	{
		if (currentbuffer == buffer)
		{
			currentbuffer = buffer2;
		}
		else
		{
			currentbuffer = buffer;
		}
		isPopulated = false;
	}

	int bufferSize = 2048;
	bool isAvailable = true;
	bool isPopulated = false;
private:
	int current = 0;
	float* currentbuffer;
	float buffer[2048];
	float buffer2[2048];
};

