#pragma once

#include "Utility/Collections/TList.h"

#include "Gameplay/Components/MeshComponent.h"

class AnimatedMeshComponent final : public MeshComponent
{
private:
	int64 m_activeAnimation;
	float m_frame;

	float m_keyframeCount;
	float m_playbackSpeed;
	float m_currentLength;

public:
	AnimatedMeshComponent(const string& meshPath);

public:
	virtual void BeginPlay() override;
	virtual void Tick(float dt) override;

	void SetActiveAnimationIndex(int64 index);

};