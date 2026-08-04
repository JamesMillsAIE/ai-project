#include "Gameplay/Components/MeshComponent.h"

#include <raylib.h>

#include <glm/gtc/quaternion.hpp>

#include "Resources.h"
#include "Gameplay/Actor.h"

MeshComponent::MeshComponent(string meshPath)
	: m_meshName{ std::move(meshPath) }, m_mesh{ nullptr }, m_meshScale{ 1.f }
{

}

MeshComponent::MeshComponent(Resource* mesh)
	: m_mesh{ mesh }, m_meshScale{ 1.f }
{
	
}

void MeshComponent::BeginPlay()
{
	if (!m_meshName.empty())
	{
		m_mesh = Resources::GetInstance().Get<Model>(m_meshName);
	}
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
			ToRaylib(owner->scale * m_meshScale), WHITE
		);
	}
}

void MeshComponent::SetMeshScale(const float scale)
{
	m_meshScale = scale;
}
