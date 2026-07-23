#include "Gameplay/Worlds/IWorld.h"

#include "Gameplay/Actor.h"
#include "Gameplay/Worlds/PhysicsWorld.h"

IWorld::IWorld()
	: m_physics{ new PhysicsWorld{ { 0.f, -1.f, 0.f } } }
{
	Actor* groundActor = new Actor{this};
	groundActor->location = { 0.f, -10.f, 0.f };
	groundActor->scale = { 100.f, 20.f, 100.f };
	groundActor->CreatePhysicsBody(0.f, 0.f, b3_staticBody);
	groundActor->color = RED;

	Actor* cubeActor = new Actor{this};
	cubeActor->location = { 0.f, 4.f, 0.f };
	cubeActor->CreatePhysicsBody(1.f, .3f, b3_dynamicBody);

	m_actors.Add(groundActor);
	m_actors.Add(cubeActor);
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
