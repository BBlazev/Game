#include "include/camera.hpp"


PlayerCamera::PlayerCamera()
{
    camera.target = { 0, 0 };
    camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.zoom = 2.0f;
    camera.rotation = 0.0f;
}

Camera2D& PlayerCamera::GetCamera()
{
    return camera;
}