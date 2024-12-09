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
	float getPanL() { return panL; }
	float getPanR() { return panR; }
	float panL;
	float panR;
	void write(int bytes, float* data, int currentFrame, float att, float leftPan, float rightPan) { 

		if (currentbuffer == buffer)
		{
			for (int i = 0; i < bytes; ++i)
			{
				buffer2[2 * i + 0] += data[currentFrame  + i] * att * leftPan;
				buffer2[2 * i + 1] += data[currentFrame + i + 1] * att * rightPan; 
			}
		}
		else
		{
			for (int i = 0; i < bytes; ++i)
			{
				buffer[2 * i + 0] += data[currentFrame + i] * att * leftPan;
				buffer[2 * i + 1] += data[currentFrame + i + 1] * att * rightPan;
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

	int bufferSize = 4096;
	bool isAvailable = true;
	bool isPopulated = false;
private:
	int current = 0;
	float* currentbuffer;
	float buffer[4096];
	float buffer2[4096];
};

