#pragma once

#include "raylib.h"

class PlayerCamera
{
public:

	PlayerCamera(int width, int height);

	int screen_width;
	int screen_height;

	Camera2D& GetCamera();

private:

	Camera2D camera{ 0 };

};