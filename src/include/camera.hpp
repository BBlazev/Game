#pragma once

#include "raylib.h"
#include "screen.hpp"
#include <memory>

class PlayerCamera
{
public:

	PlayerCamera();

	Camera2D& GetCamera();

private:

	Camera2D camera{ 0 };

};