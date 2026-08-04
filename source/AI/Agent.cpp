#include "AI/Agent.h"

#include "AI/BrainComponent.h"

Agent::Agent(IWorld* world) :
	Actor{ world }
{
	m_brain = MakeComponent<BrainComponent>();
}

void Agent::SetAgentType(AgentType* agentType)
{
	m_agentType = agentType;
}

AgentType* Agent::GetAgentType() const
{
	return m_agentType;
}
