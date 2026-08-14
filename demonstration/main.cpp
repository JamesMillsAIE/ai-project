#include <raylib/raylib.h>

int main()
{
	Camera2D camera = {};

	InitWindow(1080, 720, "Demonstration");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(camera);

		EndMode2D();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}