#pragma once

#include "Utility/Collections/TList.h"

#include "Gameplay/Components/MeshComponent.h"

class AnimatedMeshComponent final : public MeshComponent
{
private:
	TList<string> m_animationNames;
	TList<Resource*> m_animations;
	int64 m_activeAnimation;
	float m_frame;

public:
	AnimatedMeshComponent(const string& meshPath, const TList<string>& animationPaths);

public:
	virtual void BeginPlay() override;
	virtual void Tick(float dt) override;

};