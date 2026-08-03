#include "Application.h"

#include "Debugger.h"
#include "Resources.h"
#include "Gameplay/Worlds/IWorld.h"
#include "Gameplay/Worlds/MazeWorld.h"
#include "Utility/Config.h"

Application::Application()
	: m_world{ nullptr }, m_appConfig{ new Config{ "application" } }
{
	Debugger::Instance().Initialise(m_appConfig);

	// Get the window and camera setup from the config
	m_params = m_appConfig->Get<WindowParams>("window"); 
	m_camera = m_appConfig->Get<Camera>("camera");

	// Calculate the flags that the window should use based on the config
	uint32 flag = 0;
	flag |= m_params.resizable ? FLAG_WINDOW_RESIZABLE : 0;
	flag |= m_params.alwaysRun ? FLAG_WINDOW_ALWAYS_RUN : 0;
	SetConfigFlags(flag);

	// Initialise the window
	InitWindow(m_params.width, m_params.height, m_params.title.c_str());

	if (m_params.fullscreen)
	{
		// Update the window size and toggle fullscreen if requested
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
	m_world = new MazeWorld;
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
