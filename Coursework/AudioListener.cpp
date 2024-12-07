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
void AudioListener::UpdateRotation(int x, int y, int z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

vec3 AudioListener::getPosition()
{
	return position;
}

vec3 AudioListener::getRotation()
{
	return rotation;
}
