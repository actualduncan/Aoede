#pragma once

#include <iostream>

class AudioLoader;

class AoedeAudio
{
public:
	AoedeAudio();
	~AoedeAudio();
	void init();
private:
	std::unique_ptr<AudioLoader> audioLoader;
};

