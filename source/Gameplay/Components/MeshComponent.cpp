#include "Gameplay/Components/MeshComponent.h"

#include <raylib.h>

#include <glm/gtc/quaternion.hpp>

#include "Resources.h"
#include "Gameplay/Actor.h"

MeshComponent::MeshComponent(const string& meshPath)
	: m_meshName{ meshPath }, m_mesh{ nullptr }
{

}

void MeshComponent::BeginPlay()
{
	m_mesh = Resources::GetInstance().Get<Model>(m_meshName);
}

void MeshComponent::Render()
{
	if (m_mesh != nullptr)
	{
		const Actor* owner = Owner();
		const vec3 axis = glm::axis(owner->rotation);
		const float angle = glm::angle(owner->rotation);

		DrawModelEx(
			static_cast<Model>(*m_mesh), ToRaylib(owner->location), ToRaylib(axis), glm::degrees(angle),
			ToRaylib(owner->scale), WHITE
		);
	}
}