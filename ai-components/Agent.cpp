#include "Agent.h"

#include <raylib/raymath.h>

#include "IBehaviour.h"

namespace AiForGames
{
	Agent::Agent(IBehaviour* behaviour)
		:location{ Vector2Zero() }, rotation{ 0.f }, size{ Vector2One() }, m_behaviour{ behaviour }
	{

	}

	Agent::~Agent()
	{
		delete m_behaviour;
	}

	void Agent::Tick(const float dt)
	{
		if (m_behaviour != nullptr)
		{
			m_behaviour->Tick(this, dt);
		}
	}

	void Agent::Render()
	{
		if (m_behaviour != nullptr)
		{
			m_behaviour->Render(this);
		}
	}
}
