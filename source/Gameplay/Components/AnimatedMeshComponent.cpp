#include "Gameplay/Components/AnimatedMeshComponent.h"

#include "Resources.h"

#include "Gameplay/Actor.h"

AnimatedMeshComponent::AnimatedMeshComponent(const string& meshPath) :
	MeshComponent{ meshPath }, m_activeAnimation{ 0 }, m_frame{ 0.f }, m_keyframeCount{ 0.f },
	m_playbackSpeed{ 1.f }, m_currentLength{ 0.f } { }

void AnimatedMeshComponent::BeginPlay()
{
	MeshComponent::BeginPlay();

	if (m_mesh != nullptr && m_mesh->animationCount > 0)
	{
		m_keyframeCount = static_cast<float>(m_mesh->animations[m_activeAnimation].keyframeCount);
		m_currentLength = static_cast<float>(m_mesh->animations[m_activeAnimation].keyframeCount) / 60.f;
	}
}

void AnimatedMeshComponent::Tick(const float dt)
{
	MeshComponent::Tick(dt);

	if (m_mesh == nullptr)
	{
		return;
	}

	m_frame += m_playbackSpeed;

	if (m_activeAnimation < m_mesh->animationCount)
	{
		UpdateModelAnimation(static_cast<Model>(*m_mesh), m_mesh->animations[m_activeAnimation], m_frame);
	}
}

void AnimatedMeshComponent::SetActiveAnimationIndex(int64 index)
{
	if (m_mesh == nullptr)
	{
		return;
	}

	if (index > m_mesh->animationCount)
	{
		return;
	}

	m_activeAnimation = index;
	m_keyframeCount = static_cast<float>(m_mesh->animations[m_activeAnimation].keyframeCount);
	m_currentLength = static_cast<float>(m_mesh->animations[m_activeAnimation].keyframeCount) / 60.f;
}
