#include "Application.h"

#include <cstdlib>
#include <raylib/raylib.h>
#include <raylib/raymath.h>

#include "Agent.h"
#include "NodeGraph.h"

namespace AiForGames
{
	Application::Application() :
		m_width{ 1280 }, m_height{ 960 }, m_title{ "AI For Games - Demonstration" }
	{
		m_camera =
		{
			.offset = Vector2Zero(),
			.target = Vector2Zero(),
			.rotation = 0,
			.zoom = 1.f
		};
	}

	int32_t Application::Run()
	{
		// Attempt to open the window, returning failure if it failed to open
		InitWindow(m_width, m_height, m_title);

		if (!IsWindowReady())
		{
			return EXIT_FAILURE;
		}

		BeginPlay();

		while (!WindowShouldClose())
		{
			Tick(GetFrameTime());

			// Begin the render step using black as the background and the current
			// camera setup
			BeginDrawing();
			ClearBackground(BLACK);
			BeginMode2D(m_camera);

			Render();

			// Finish the render step.
			EndMode2D();
			EndDrawing();
		}

		EndPlay();

		CloseWindow();

		// All systems ran fine, so return success
		return EXIT_SUCCESS;
	}

	void Application::BeginPlay()
	{
		m_graph = new NodeGraph{ LoadImage("Resources/node_map.png"), 32.f };
	}

	void Application::Tick(const float dt) const
	{
		for (Agent* agent : m_agents)
		{
			agent->Tick(dt);
		}
	}

	void Application::Render() const
	{
		m_graph->Render();

		for (Agent* agent : m_agents)
		{
			agent->Render();
		}
	}

	void Application::EndPlay() const
	{
		delete m_graph;

		for (const Agent* agent : m_agents)
		{
			delete agent;
		}
	}
}
