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
	Agent(IWorld* world, const string& agentType = "default");
	~Agent() override;

public:
	void SetAgentType(AgentType* agentType);
	[[nodiscard]] AgentType* GetAgentType() const;

};