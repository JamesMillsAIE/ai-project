#include "AI/BrainComponent.h"

#include "AI/Agent.h"
#include "AI/IBehaviour.h"

void BrainComponent::Tick(float dt)
{
	if (m_behaviour != nullptr)
	{
		m_behaviour->Tick(dt, dynamic_cast<Agent*>(Owner()));
	}
}

void BrainComponent::Render()
{
	if (m_behaviour != nullptr)
	{
		m_behaviour->Render(dynamic_cast<Agent*>(Owner()));
	}
}

IBehaviour* BrainComponent::GetBehaviour() const
{
	return m_behaviour;
}

void BrainComponent::SetBehaviour(IBehaviour* newBehaviour)
{
	m_behaviour = newBehaviour;
}