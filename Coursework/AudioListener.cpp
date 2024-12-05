#include "AudioListener.h"

AudioListener::AudioListener()
{

}

AudioListener::~AudioListener()
{

}

void AudioListener::UpdatePosition(int x, int y, int z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

vec3 AudioListener::getPosition()
{
	return position;
}
