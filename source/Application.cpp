#include "Application.h"

#include <utility>

#include "Resources.h"
#include "World.h"

Application::Application(const int w, const int h, string title, const Color clrCol)
	: m_width{ w }, m_height{ h }, m_title{ std::move(title) }, m_clearColor{ clrCol }, m_world{ nullptr }
{
	InitWindow(m_width, m_height, m_title.c_str());
}

Application::~Application()
{
	Resources::GetInstance().Clear();
	CloseWindow();
}

int Application::Run()
{
	if (!IsWindowReady())
	{
		return EXIT_FAILURE;
	}

	BeginPlay();

	while (!WindowShouldClose())
	{
		Tick(GetFrameTime());

		BeginDrawing();
		ClearBackground(m_clearColor);

		Render();

		EndDrawing();
	}

	EndPlay();

	return EXIT_SUCCESS;
}

void Application::BeginPlay()
{
	m_world = new World;
}

void Application::Tick(const float dt)
{
	m_world->Tick(dt);
}

void Application::Render() { }

void Application::EndPlay()
{
	delete m_world;
}
