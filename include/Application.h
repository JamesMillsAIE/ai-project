#pragma once

#include <raylib.h>
#include <string>
#include <nlohmann/json.hpp>

#include "Common.h"

using std::string;

class Config;
class IWorld;

struct WindowParams
{
	int32 width;
	int32 height;
	string title;
	bool resizable;
	bool alwaysRun;
	bool fullscreen;
	Color clearColor;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(WindowParams, width, height, title, resizable, alwaysRun, fullscreen, clearColor)
};

class Application
{
private:
	WindowParams m_params;
	Camera3D m_camera;

	IWorld* m_world;
	Config* m_appConfig;

public:
	Application();
	~Application();

public:
	int32 Run();

private:
	void BeginPlay();

	void Tick(float dt);
	void Render() const;

	void EndPlay() const;

};