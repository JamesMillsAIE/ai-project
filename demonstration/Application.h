#pragma once

#include <cstdint>
#include <vector>
#include <raylib/raylib.h>

using std::vector;

namespace AiForGames
{
	class NodeGraph;
	class Agent;

	class Application
	{
	private:
		int32_t m_width;
		int32_t m_height;
		const char* m_title;

		Camera2D m_camera;
		float m_cameraSpeed;

		vector<Agent*> m_agents;
		NodeGraph* m_graph;

	public:
		Application();

	public:
		int32_t Run();

	private:
		void BeginPlay();

		void Tick(float dt);
		void Render() const;

		void EndPlay() const;

	};
}
