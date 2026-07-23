#pragma once

#include <box3d/types.h>

#include "Common.h"
#include "Maths.h"

class PhysicsWorld
{
	friend class IWorld;

private:
	b3WorldId m_world;
	vec3 m_gravity;

	float m_timeStep;
	int32 m_subSteps;

private:
	PhysicsWorld(vec3 gravity, float timeStep = 1.f / 60.f, int32 subSteps = 4);
	~PhysicsWorld();

private:
	void Simulate();

};