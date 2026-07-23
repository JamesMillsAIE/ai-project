#pragma once

#include <functional>
#include <box3d/types.h>

#include "Common.h"
#include "Maths.h"
#include "Utility/Collections/TList.h"

using PhysicsSimulationCallback = std::function<void()>;

class PhysicsWorld
{
	friend class IWorld;

private:
	struct SimulatedActorBody
	{
		b3BodyId body;
		PhysicsSimulationCallback callback;
	};

private:
	b3WorldId m_worldId;
	vec3 m_gravity;

	float m_timeStep;
	int32 m_subSteps;

	TList<SimulatedActorBody> m_simulatedActorBodies;

private:
	explicit PhysicsWorld(vec3 gravity, float timeStep = 1.f / 60.f, int32 subSteps = 4);
	~PhysicsWorld();

public:
	void AddBody(b3BodyId body, PhysicsSimulationCallback callback);

	[[nodiscard]] const b3WorldId& GetWorldID() const;

private:
	void Simulate();

};
