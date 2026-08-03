#pragma once

#include <raylib.h>
#include <string>

#include "Common.h"

using std::string;

class Config;
class IWorld;

class Application
{
private:
	int32 m_width;
	int32 m_height;
	string m_title;
	Color m_clearColor;
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