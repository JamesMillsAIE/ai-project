#pragma once

#include "Gameplay/Actor.h"

class BrainComponent;
struct AgentType;

class Agent final : public Actor
{
	friend IWorld;

private:
	AgentType* m_agentType;
	BrainComponent* m_brain;
	
protected:
	explicit Agent(IWorld* world);
	~Agent() override;

public:
	void SetAgentType(AgentType* agentType);

};