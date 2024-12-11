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
void AudioListener::UpdateRotation(float x, float y, float z)
{
	PrevRotation = rotation;
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

void AudioListener::UpdateRight(float x, float y, float z)
{
	PrevRotation = rotation;
	right.x = x;
	right.y = y;
	right.z = z;
}


vec3 AudioListener::getPosition()
{
	return position;
}

vec3 AudioListener::getRotation()
{
	return rotation;
}

vec3 AudioListener::getPreviousRotation()
{
	return PrevRotation;
}
