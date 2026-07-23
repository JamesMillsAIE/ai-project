#include "Gameplay/Worlds/PhysicsWorld.h"

#include <box3d/box3d.h>

#include <utility>

PhysicsWorld::PhysicsWorld(const vec3 gravity, const float timeStep, const int32 subSteps)
	: m_worldId{  }, m_gravity{ gravity }, m_timeStep{ timeStep }, m_subSteps{ subSteps }
{
	b3WorldDef worldDef = b3DefaultWorldDef();
	worldDef.gravity = ToBox3d(gravity);

	m_worldId = b3CreateWorld(&worldDef);
}

PhysicsWorld::~PhysicsWorld()
{
	b3DestroyWorld(m_worldId);
}

void PhysicsWorld::AddBody(const b3BodyId body, PhysicsSimulationCallback callback)
{
	m_simulatedActorBodies.Add({ .body = body, .callback = std::move(callback) });
}

const b3WorldId& PhysicsWorld::GetWorldID() const
{
	return m_worldId;
}

void PhysicsWorld::Simulate()
{
	b3World_Step(m_worldId, m_timeStep, m_subSteps);

	for (const auto& [body, callback] : m_simulatedActorBodies)
	{
		callback();
	}
}
