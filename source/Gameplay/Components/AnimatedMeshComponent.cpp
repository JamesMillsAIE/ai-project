#include "Gameplay/Components/AnimatedMeshComponent.h"

#include "Resources.h"

#include "Gameplay/Actor.h"

AnimatedMeshComponent::AnimatedMeshComponent(const string& meshPath, const TList<string>& animationPaths)
	: MeshComponent{ meshPath }, m_animationNames{ animationPaths }, m_activeAnimation{ 0 }, m_frame{ 0.f }
{}

void AnimatedMeshComponent::BeginPlay()
{
	MeshComponent::BeginPlay();

	Resources& resources = Resources::GetInstance();

	for (string& animationName : m_animationNames)
	{
		Resource* animation = resources.Get<ModelAnimation>(animationName);

		if (animation != nullptr)
		{
			m_animations.Add(animation);
		}
	}
}

void AnimatedMeshComponent::Tick(float dt)
{
	MeshComponent::Tick(dt);

	m_frame += dt;

	if (m_activeAnimation < m_animations.Count())
	{
		const Resource* animation = m_animations[m_activeAnimation];

		for (int32 i = 0; i < animation->animationCount; ++i)
		{
			UpdateModelAnimation(static_cast<Model>(*m_mesh), animation->animations[i], m_frame);
		}
	}
}
