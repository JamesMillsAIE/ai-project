#include "Application.h"

#include <utility>

#include "Debugger.h"
#include "Resources.h"
#include "Gameplay/Worlds/IWorld.h"
#include "Utility/Config.h"

Application::Application()
	: m_world{ nullptr }, m_appConfig{ new Config{ "application" } }
{
	Debugger::Instance().Initialise(m_appConfig);

	m_width = m_appConfig->Get<int32>("window.width");
	m_height = m_appConfig->Get<int32>("window.height");
	m_title = m_appConfig->Get<string>("window.title");
	m_clearColor = m_appConfig->Get<Color>("window.clrColor");
	m_camera = m_appConfig->Get<Camera>("camera");

	InitWindow(m_width, m_height, m_title.c_str());
}

Application::~Application()
{
	delete m_appConfig;

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
		Debugger::Instance().TickEnabledFlag();

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
