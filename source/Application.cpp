#include "Application.h"

#include <utility>

#include "Resources.h"
#include "Gameplay/Worlds/IWorld.h"

Application::Application(const int32 w, const int32 h, string title, const Color clrCol)
	: m_width{ w }, m_height{ h }, m_title{ std::move(title) }, m_clearColor{ clrCol }, m_camera{
		  .position   = { 0.f, 1.f, -10.f }, .target = { 0.f, 1.f, -9.f }, .up = { 0.f, 1.f, 0.f }, .fovy = 90.f,
		  .projection = CAMERA_PERSPECTIVE
	  },
	  m_world{ nullptr }
{
	InitWindow(m_width, m_height, m_title.c_str());
}

Application::~Application()
{
	Resources::GetInstance().Clear();
	CloseWindow();
}

int32 Application::Run()
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

		BeginMode3D(m_camera);
		Render();
		EndMode3D();

		EndDrawing();
	}

	EndPlay();

	return EXIT_SUCCESS;
}

void Application::BeginPlay()
{
	m_world = new IWorld;
}

void Application::Tick(const float dt)
{
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		HideCursor();
	}
	else if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
	{
		ShowCursor();
	}

	if (IsCursorHidden())
	{
		UpdateCamera(&m_camera, CAMERA_FREE);
	}

	m_world->Tick(dt);
}

void Application::Render()
{
	m_world->Render();
}

void Application::EndPlay()
{
	delete m_world;
}
