#pragma once

#include "AudioHelpers.h"

class AudioListener
{
public:
	AudioListener();
	~AudioListener();

	void UpdatePosition(int x, int y, int z);

	vec3 getPosition();
private:

	vec3 position;
	vec3 rotation;
};

