#pragma once

#include <functional>

#include <box3d/box3d.h>

#include "Maths.h"

#include "Utility/Collections/TList.h"

class IComponent;
class IWorld;

using ComponentListChange = std::function<void()>;

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
	
	TList<IComponent*> m_components;
	TList<ComponentListChange> m_componentListChanges;

protected:
	explicit Actor(IWorld* world);
	virtual ~Actor();

public:
	virtual void BeginPlay();

	virtual void Tick(float dt);
	virtual void Render();

	virtual void EndPlay();

	template<typename T, typename... ARGS>
	T* MakeComponent(ARGS... args);

	void DestroyComponent(IComponent* component);

private:
	void ApplyComponentListChanges();

};

template <typename T, typename... ARGS>
T* Actor::MakeComponent(ARGS... args)
{
	static_assert(std::is_base_of_v<IComponent, T>, "T must derive from IComponent");

	T* newComp = new T{ args... };
	m_componentListChanges.Add([this, newComp]
		{
			newComp->BeginPlay();
			m_components.Add(newComp);
		});

	newComp->m_owner = this;
	return newComp;
}