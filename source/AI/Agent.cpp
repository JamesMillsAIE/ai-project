#include "AI/Agent.h"

#include "Debugger.h"
#include "AI/IBehaviour.h"

Agent::Agent(IWorld* world)
	: Actor{ world }, m_behaviour{ nullptr }
{

}

Agent::~Agent()
{
	delete m_behaviour;
}

void Agent::Tick(float dt)
{
	if (m_behaviour != nullptr)
	{
		m_behaviour->Tick(dt, this);
	}
}

void Agent::Render()
{
	if (m_behaviour != nullptr)
	{
		m_behaviour->Render(this);
	}

	Debugger::Instance().DrawDebugCapsule(location, { 0.f, 1.f, 0.f }, .9f, 1.f, RED);
}

void Agent::SetBehaviour(IBehaviour* behaviour)
{
	m_behaviour = behaviour;
}
