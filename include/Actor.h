#pragma once

#include <box3d/box3d.h>
#include "Maths.h"

class Actor
{
public:
	vec3 location;
	quat rotation;
	vec3 scale;

private:
	b3BodyId m_physicsBody;

public:
	Actor();
	virtual ~Actor() = default;

public:
	virtual void Tick(float dt);
	virtual void Render();

};