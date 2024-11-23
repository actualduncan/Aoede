#pragma once
struct vec3
{
	int x, y, z;
};

struct AudioDesc
{
	const char* filename = "";
	float volume = 1.0f;
	bool isLooping = false;
};

class AudioHandle
{
public:
	AudioHandle(const char* handleName, AudioDesc desc) : m_handleName(handleName), m_desc(desc) {}
	const char* getName() { return m_handleName; }
	AudioDesc getDesc() { return m_desc; }
private:
	const char* m_handleName = "";
	AudioDesc m_desc;
};
