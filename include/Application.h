#pragma once

#include <raylib.h>
#include <string>

using std::string;

class Application
{
private:
	int m_width;
	int m_height;
	string m_title;
	Color m_clearColor;

public:
	Application(int w, int h, string  title, Color clrCol);
	~Application();

public:
	int Run();

private:
	void BeginPlay();

	void Tick(float dt);
	void Render();

	void EndPlay();

};