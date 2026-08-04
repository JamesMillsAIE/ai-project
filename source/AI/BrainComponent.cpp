#include "AI/BrainComponent.h"

#include "Debugger.h"

#include "AI/Agent.h"
#include "AI/IBehaviour.h"
#include "AI/Navigation/Navigation.h"

BrainComponent::BrainComponent(IBehaviour* defaultBehaviour)
	: m_behaviour{ defaultBehaviour }
{
	
}

void BrainComponent::Tick(float dt)
{
	if (m_behaviour != nullptr)
	{
		m_behaviour->Tick(dt, OwningAgent());
	}
}

void BrainComponent::Render()
{
	if (m_behaviour != nullptr)
	{
		m_behaviour->Render(OwningAgent());
	}

	if (Agent* agent = OwningAgent())
	{
		if (AgentType* type = agent->GetAgentType())
		{
			constexpr vec3 up = { 0.f, 1.f, 0.f };
			const vec3 location = agent->location + up * (type->halfHeight * 2.f);

			Debugger::Instance().DrawDebugCapsule(
				location, up, type->halfHeight, type->radius, { 0, 0, 255, 128 }
			);
		}
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

Agent* BrainComponent::OwningAgent() const
{
	return dynamic_cast<Agent*>(Owner());
}
