#include "Gameplay/Worlds/IWorld.h"

#include "AI/Agent.h"
#include "Gameplay/Actor.h"
#include "Gameplay/Worlds/PhysicsWorld.h"

IWorld::IWorld()
	: m_physics{ new PhysicsWorld }
{
	Agent* agent = new Agent{ this };
	m_actors.Add(agent);
}

IWorld::~IWorld()
{
	delete m_physics;
}

void IWorld::Tick(float dt)
{
	m_physics->Simulate();

	for (Actor* actor : m_actors)
	{
		actor->Tick(dt);
	}
}

void IWorld::Render()
{
	for (Actor* actor : m_actors)
	{
		actor->Render();
	}
}

PhysicsWorld* IWorld::GetPhysicsWorld() const
{
	return m_physics;
}
