#pragma once
#include <string>

struct vec3
{
	float x, y, z;
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
	AudioHandle() {};
	AudioHandle(std::string handleName, AudioDesc desc) : m_handleName(handleName), m_desc(desc) {}
	AudioHandle(std::string handleName, AudioDesc desc, float x, float y, float z) : m_handleName(handleName), m_desc(desc) { m_position.x = x; m_position.y = y; m_position.z = z; }
	std::string getName() { return m_handleName.c_str(); }
	AudioDesc getDesc() { return m_desc; }
	vec3 getPosition() { return m_position; };
	void setPosition(vec3 position) { m_position = position; }
private:
	std::string m_handleName = "";
	AudioDesc m_desc;
	vec3 m_position;
};


