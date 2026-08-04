#include "Gameplay/Worlds/PhysicsWorld.h"

#include <box3d/box3d.h>

#include <utility>

#include "Utility/Config.h"

PhysicsWorld::PhysicsWorld()
	: m_config{ new Config{ "physics" } }, m_worldId{  }
{
	m_gravity = ToGlm(m_config->Get<Vector3>("gravity"));
	m_timeStep = m_config->Get<float>("simulation.timeStep");
	m_subSteps = m_config->Get<int32>("simulation.substeps");

	b3WorldDef worldDef = b3DefaultWorldDef();
	worldDef.gravity = ToBox3d(m_gravity);

	m_worldId = b3CreateWorld(&worldDef);
}

PhysicsWorld::~PhysicsWorld()
{
	delete m_config;

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
