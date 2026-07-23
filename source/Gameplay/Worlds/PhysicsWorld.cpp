#include "Gameplay/Worlds/PhysicsWorld.h"

#include <box3d/box3d.h>

PhysicsWorld::PhysicsWorld(const vec3 gravity, const float timeStep, const int32 subSteps)
	: m_gravity{ gravity }, m_world{  }, m_timeStep{ timeStep }, m_subSteps{ subSteps }
{
	b3WorldDef worldDef = {};
	worldDef.gravity = ToBox3d(gravity);

	m_world = b3CreateWorld(&worldDef);
}

PhysicsWorld::~PhysicsWorld()
{
	b3DestroyWorld(m_world);
}

void PhysicsWorld::Simulate()
{
	b3World_Step(m_world, m_timeStep, m_subSteps);
}
