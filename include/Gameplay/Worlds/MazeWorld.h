#pragma once

#include "IWorld.h"

struct Resource;

class MazeWorld final : public IWorld
{
private:
	Resource* m_customModel;

public:
	MazeWorld();
	~MazeWorld() override;

};