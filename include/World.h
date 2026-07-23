#pragma once

class PhysicsWorld;

class World
{
private:
	PhysicsWorld* m_physics;

public:
	World();
	~World();

public:
	void Tick(float dt);

};