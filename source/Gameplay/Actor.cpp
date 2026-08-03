#include "Gameplay/Actor.h"

#include "Gameplay/IComponent.h"
#include "Gameplay/Worlds/PhysicsWorld.h"

Actor::Actor(IWorld* world)
	: location{ 0.f }, rotation{ 1.f, 0.f, 0.f, 0.f }, scale{ 1.f }, color{ WHITE }, m_world{ world }
{}

Actor::~Actor()
{
	for (IComponent* component : m_components)
	{
		DestroyComponent(component);
	}

	ApplyComponentListChanges();
}

void Actor::BeginPlay()
{}

void Actor::Tick(float dt)
{}

void Actor::Render()
{}

void Actor::EndPlay()
{}

void Actor::DestroyComponent(IComponent* component)
{
	m_componentListChanges.Add([this, component]
		{
			m_components.Remove(component);
			component->EndPlay();
			delete component;
		});
}

void Actor::ApplyComponentListChanges()
{
	for (const ComponentListChange& change : m_componentListChanges)
	{
		change();
	}

	m_componentListChanges.Clear();
}

//void Actor::CreatePhysicsBody(const float density, const float friction, const b3BodyType type)
//{
//	PhysicsWorld* physicsWorld = m_world->GetPhysicsWorld();
//
//	b3BodyDef def = b3DefaultBodyDef();
//	def.type      = type;
//	def.position  = ToBox3d(location);
//
//	m_physicsBody = b3CreateBody(physicsWorld->GetWorldID(), &def);
//
//	const b3Vec3 extents = ToBox3d(scale * .5f);
//	m_hull               = b3MakeBoxHull(extents.x, extents.y, extents.z);
//
//	b3ShapeDef shapeDef            = b3DefaultShapeDef();
//	shapeDef.density               = density;
//	shapeDef.baseMaterial.friction = friction;
//
//	m_physicsShape = b3CreateHullShape(m_physicsBody, &shapeDef, &m_hull.base);
//
//	physicsWorld->AddBody(m_physicsBody, [this]
//	{
//		location = ToGlm(b3Body_GetPosition(m_physicsBody));
//		rotation = ToGlm(b3Body_GetRotation(m_physicsBody));
//	});
//}
