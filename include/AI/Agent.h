#pragma once

#include "Gameplay/Actor.h"

struct AgentType;
class IBehaviour;

class Agent final : public Actor
{
	friend IWorld;

private:
	AgentType* m_agentType;
	IBehaviour* m_behaviour;

protected:
	explicit Agent(IWorld* world);
	~Agent() override;

public:
	void Tick(float dt) override;
	void Render() override;

	void SetBehaviour(IBehaviour* behaviour);
	void SetAgentType(AgentType* agentType);

};