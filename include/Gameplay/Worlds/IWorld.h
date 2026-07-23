#pragma once

#include "Utility/Collections/TList.h"

class Actor;
class PhysicsWorld;

class IWorld
{
private:
	TList<Actor*> m_actors;
	PhysicsWorld* m_physics;

public:
	IWorld();
	~IWorld();

public:
	void Tick(float dt);

};