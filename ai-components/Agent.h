#pragma once

#include <raylib/raylib.h>

namespace AiForGames
{
	class IBehaviour;

	class Agent
	{
	public:
		Vector2 location;
		float rotation;
		Vector2 size;

	private:
		IBehaviour* m_behaviour;

	public:
		Agent(IBehaviour* behaviour);
		~Agent();

	public:
		void Tick(float dt);
		void Render();

	};
}
