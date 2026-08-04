#include "AI/Agent.h"

#include "AI/BrainComponent.h"
#include "AI/Navigation/Navigation.h"

#include "Gameplay/Components/AnimatedMeshComponent.h"

Agent::Agent(IWorld* world, const string& agentType) :
	Actor{ world }
{
	m_brain = MakeComponent<BrainComponent>();
	AnimatedMeshComponent* mesh = MakeComponent<AnimatedMeshComponent>(
		"Models/SM_YBot", TList<string>{ "Animations/A_Walk" }
	);

	Navigation& navigation = Navigation::GetInstance();
	m_agentType = navigation.FindAgentType(agentType);
}

Agent::~Agent()
{}

void Agent::SetAgentType(AgentType* agentType)
{
	m_agentType = agentType;
}

AgentType* Agent::GetAgentType() const
{
	return m_agentType;
}
