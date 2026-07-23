#pragma once

#include <raylib.h>
#include <string>

#include "Common.h"

using std::string;

class IWorld;

class Application
{
private:
	int32 m_width;
	int32 m_height;
	string m_title;
	Color m_clearColor;

	IWorld* m_world;

public:
	Application(int32 w, int32 h, string  title, Color clrCol);
	~Application();

public:
	int32 Run();

private:
	void BeginPlay();

	void Tick(float dt);
	void Render();

	void EndPlay();

};