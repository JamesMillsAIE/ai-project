#pragma once

#include <string>

#include "Gameplay/Actor.h"

class BrainComponent;
struct AgentType;

using std::string;

class Agent final : public Actor
{
	friend IWorld;

private:
	AgentType* m_agentType;
	BrainComponent* m_brain;
	
protected:
	explicit Agent(IWorld* world);

public:
	void SetAgentType(AgentType* agentType);
	[[nodiscard]] AgentType* GetAgentType() const;

};