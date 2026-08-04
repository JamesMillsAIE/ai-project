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

public:
	MeshComponent(const string& meshPath);

public:
	virtual void BeginPlay() override;
	virtual void Render() override;

};