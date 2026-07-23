#include "Gameplay/Actor.h"

#include "Gameplay/Worlds/IWorld.h"
#include "Gameplay/Worlds/PhysicsWorld.h"

Actor::Actor(IWorld* world)
	: location{ 0.f }, rotation{ 1.f, 0.f, 0.f, 0.f }, scale{ 1.f }, color{ WHITE }, m_world{ world },
	  m_physicsBody{ }, m_physicsShape{ }, m_hull{ } { }

void Actor::Tick(float dt) { }

void Actor::Render()
{
	DrawCubeV(ToRaylib(location), ToRaylib(scale), color);
	DrawCubeWiresV(ToRaylib(location), ToRaylib(scale), BLACK);
}

void Actor::CreatePhysicsBody(const float density, const float friction, const b3BodyType type)
{
	PhysicsWorld* physicsWorld = m_world->GetPhysicsWorld();

	b3BodyDef def = b3DefaultBodyDef();
	def.type      = type;
	def.position  = ToBox3d(location);

	m_physicsBody = b3CreateBody(physicsWorld->GetWorldID(), &def);

	const b3Vec3 extents = ToBox3d(scale * .5f);
	m_hull               = b3MakeBoxHull(extents.x, extents.y, extents.z);

	b3ShapeDef shapeDef            = b3DefaultShapeDef();
	shapeDef.density               = density;
	shapeDef.baseMaterial.friction = friction;

	m_physicsShape = b3CreateHullShape(m_physicsBody, &shapeDef, &m_hull.base);

	physicsWorld->AddBody(m_physicsBody, [this]
	{
		location = ToGlm(b3Body_GetPosition(m_physicsBody));
		rotation = ToGlm(b3Body_GetRotation(m_physicsBody));
	});
}
