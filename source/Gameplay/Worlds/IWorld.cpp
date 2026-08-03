#include "Gameplay/Worlds/IWorld.h"

#include "Gameplay/Actor.h"
#include "Gameplay/IComponent.h"
#include "Gameplay/Worlds/PhysicsWorld.h"

IWorld::IWorld()
	: m_physics{ new PhysicsWorld }
{

}

IWorld::~IWorld()
{
	for (Actor* actor : m_actors)
	{
		delete actor;
	}
	m_actors.Clear();

	delete m_physics;
}

void IWorld::Tick(float dt)
{
	for (const ActorListChange& change : m_actorListChanges)
	{
		change();
	}

	m_actorListChanges.Clear();

	m_physics->Simulate();

	for (Actor* actor : m_actors)
	{
		actor->ApplyComponentListChanges();

		for (IComponent* component : actor->m_components)
		{
			component->Tick(dt);
		}

		actor->Tick(dt);
	}
}

void IWorld::Render()
{
	for (Actor* actor : m_actors)
	{
		for (IComponent* component : actor->m_components)
		{
			component->Render();
		}

		actor->Render();
	}
}

PhysicsWorld* IWorld::GetPhysicsWorld() const
{
	return m_physics;
}

void IWorld::DestroyActor(Actor* actor)
{
	m_actorListChanges.Add([this, actor]
		{
			actor->EndPlay();
			actor->ApplyComponentListChanges();

			m_actors.Remove(actor);
			delete actor;
		});
}
