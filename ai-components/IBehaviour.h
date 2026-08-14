#pragma once

namespace AiForGames
{
	class Agent;

	class IBehaviour
	{
	public:
		virtual ~IBehaviour() = default;

	public:
		virtual void Tick(Agent* agent, float dt) = 0;
		virtual void Render(Agent* agent)
		{}

	};
}
