#pragma once

#include "AudioHelpers.h"

class AudioListener
{
public:
	AudioListener();
	~AudioListener();

	void UpdatePosition(int x, int y, int z);
	void UpdateRotation(int x, int y, int z);
	vec3 getPosition();
	vec3 getRotation();
private:

	vec3 position;
	vec3 rotation;
};

