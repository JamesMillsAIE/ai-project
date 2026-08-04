#pragma once

#include <string>

#include "Gameplay/IComponent.h"

struct Resource;

using std::string;

class MeshComponent : public IComponent
{
protected:
	string m_meshName;
	Resource* m_mesh;
	float m_meshScale;

public:
	MeshComponent(const string& meshPath);

public:
	virtual void BeginPlay() override;
	virtual void Render() override;

	void SetMeshScale(float scale);

};