#include "Gameplay/Components/AnimatedMeshComponent.h"

#include "Resources.h"

#include "Gameplay/Actor.h"

AnimatedMeshComponent::AnimatedMeshComponent(const string& meshPath) :
	MeshComponent{ meshPath }, m_animations{ nullptr }, m_activeAnimation{ 0 }, m_frame{ 0.f }
{}

void AnimatedMeshComponent::BeginPlay()
{
	MeshComponent::BeginPlay();

	Resources& resources = Resources::GetInstance();
	m_animations = resources.Get<ModelAnimation>(m_meshName);
}

void AnimatedMeshComponent::Tick(const float dt)
{
	MeshComponent::Tick(dt);

	m_frame += dt;

	if (m_animations == nullptr)
	{
		return;
	}

	if (m_activeAnimation < m_animations->animationCount)
	{
		UpdateModelAnimation(static_cast<Model>(*m_mesh), m_animations->animations[m_activeAnimation], m_frame);
	}
}
