#include "World.h"

#include "PhysicsWorld.h"

World::World()
	: m_physics{ new PhysicsWorld{ { 0.f, -10.f, 0.f } } }
{

}

World::~World()
{
	delete m_physics;
}

void World::Tick(float dt)
{
	m_physics->Simulate();
}
