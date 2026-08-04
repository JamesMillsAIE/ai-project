#include "AI/Agent.h"

#include "AI/BrainComponent.h"
#include "AI/Navigation/Navigation.h"

#include "Gameplay/Components/AnimatedMeshComponent.h"

Agent::Agent(IWorld* world) :
	Actor{ world }, m_agentType{ nullptr }
{
	m_brain = MakeComponent<BrainComponent>();
	MakeComponent<AnimatedMeshComponent>("Models/SM_YBot", TList<string>{ "Animations/A_Walk" });
}

Agent::~Agent()
{}

void Agent::SetAgentType(AgentType* agentType)
{
	m_agentType = agentType;
}