#include "Gameplay/Worlds/IWorld.h"

#include "Gameplay/Worlds/PhysicsWorld.h"

IWorld::IWorld()
	: m_physics{ new PhysicsWorld{ { 0.f, -10.f, 0.f } } }
{

}

IWorld::~IWorld()
{
	delete m_physics;
}

void IWorld::Tick(float dt)
{
	m_physics->Simulate();
}
