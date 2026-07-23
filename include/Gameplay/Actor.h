#pragma once

#include <box3d/box3d.h>
#include "Maths.h"

class IWorld;

class Actor
{
	friend IWorld;

public:
	vec3 location;
	quat rotation;
	vec3 scale;
	Color color;

private:
	IWorld* m_world;
	b3BodyId m_physicsBody;
	b3ShapeId m_physicsShape;
	b3BoxHull m_hull; // TODO: Make this allow all hulls

private:
	explicit Actor(IWorld* world);
	virtual ~Actor() = default;

public:
	virtual void Tick(float dt);
	virtual void Render();

	void CreatePhysicsBody(float density, float friction, b3BodyType type);

};