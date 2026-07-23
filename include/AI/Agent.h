#pragma once

#include "Gameplay/Actor.h"

class IBehaviour;

class Agent final : public Actor
{
private:
	IBehaviour* m_behaviour;

public:
	Agent();
	~Agent() override;

public:
	void Tick(float dt) override;
	void Render() override;

};