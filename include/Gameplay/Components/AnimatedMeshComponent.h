#pragma once

#include "Utility/Collections/TList.h"

#include "Gameplay/Components/MeshComponent.h"

class AnimatedMeshComponent final : public MeshComponent
{
private:
	Resource* m_animations;
	int64 m_activeAnimation;
	float m_frame;

public:
	AnimatedMeshComponent(const string& meshPath);

public:
	virtual void BeginPlay() override;
	virtual void Tick(float dt) override;

};