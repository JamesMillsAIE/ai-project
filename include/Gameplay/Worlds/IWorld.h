#pragma once

#include <functional>

#include "Utility/Collections/TList.h"

class Actor;
class PhysicsWorld;

using ActorListChange = std::function<void()>;

class IWorld
{
private:
	TList<Actor*> m_actors;
	TList<ActorListChange> m_actorListChanges;

	PhysicsWorld* m_physics;

public:
	IWorld();
	virtual ~IWorld();

public:
	void Tick(float dt);
	void Render();

	[[nodiscard]] PhysicsWorld* GetPhysicsWorld() const;

	template<typename T, typename... ARGS>
	T* MakeActor(ARGS... args);

	void DestroyActor(Actor* actor);

};

template <typename T, typename ... ARGS>
T* IWorld::MakeActor(ARGS... args)
{
	static_assert(std::is_base_of_v<Actor, T>, "T must derive from Actor");

	T* actor = new T{ this, args... };
	m_actorListChanges.Add([this, actor]()
		{
			actor->BeginPlay();
			actor->ApplyComponentListChanges();

			m_actors.Add(actor);
		});

	return actor;
}