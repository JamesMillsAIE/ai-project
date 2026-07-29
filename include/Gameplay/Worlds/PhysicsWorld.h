#pragma once

#include <functional>
#include <box3d/types.h>

#include "Common.h"
#include "Maths.h"
#include "Utility/Collections/TList.h"

using PhysicsSimulationCallback = std::function<void()>;

class Config;

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
	Config* m_config;

	b3WorldId m_worldId;
	vec3 m_gravity;

	float m_timeStep;
	int32 m_subSteps;

	TList<SimulatedActorBody> m_simulatedActorBodies;

private:
	PhysicsWorld();
	~PhysicsWorld();

public:
	void AddBody(b3BodyId body, PhysicsSimulationCallback callback);

	[[nodiscard]] const b3WorldId& GetWorldID() const;

private:
	void Simulate();

};
