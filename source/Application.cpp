#include "Application.h"

#include "Debugger.h"
#include "Resources.h"
#include "Gameplay/Worlds/IWorld.h"
#include "Utility/Config.h"

Application::Application()
	: m_world{ nullptr }, m_appConfig{ new Config{ "application" } }
{
	Debugger::Instance().Initialise(m_appConfig);

	m_params = m_appConfig->Get<WindowParams>("window"); 
	m_camera = m_appConfig->Get<Camera>("camera");

	uint32 flag = 0;

	flag |= m_params.resizable ? FLAG_WINDOW_RESIZABLE : 0;
	flag |= m_params.alwaysRun ? FLAG_WINDOW_ALWAYS_RUN : 0;
	flag |= m_params.alwaysRun ? FLAG_FULLSCREEN_MODE : 0;

	SetConfigFlags(flag);
	InitWindow(m_params.width, m_params.height, m_params.title.c_str());

	if (m_params.fullscreen)
	{
		const int monitor = GetCurrentMonitor();

		SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
		ToggleFullscreen();
	}
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
		ClearBackground(m_params.clearColor);

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

void Application::Render() const
{
	m_world->Render();
}

void Application::EndPlay() const
{
	delete m_world;
}
