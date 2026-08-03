#include "AI/Agent.h"

#include "AI/BrainComponent.h"
#include "AI/Navigation/Navigation.h"

Agent::Agent(IWorld* world) :
	Actor{ world }, m_agentType{ nullptr }
{
	m_brain = MakeComponent<BrainComponent>();
}

Agent::~Agent()
{}

void Agent::SetAgentType(AgentType* agentType)
{
	m_agentType = agentType;
}