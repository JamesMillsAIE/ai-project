#pragma once

#include "Common.h"
#include "Maths.h"

class Config;

class Debugger
{
	friend class Application;

private:
	bool m_enabled;
	int32 m_debugKey;

	int32 m_sphereSlices;
	int32 m_sphereRings;

public:
	static Debugger& Instance();

private:
	Debugger() = default;
	~Debugger() = default;

public:
	void DrawDebugCapsule(vec3 location, vec3 up, float halfHeight, float radius, Color color) const;

private:
	void Initialise(Config* config);
	void TickEnabledFlag();

};