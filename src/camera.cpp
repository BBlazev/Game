#include "include/camera.hpp"


PlayerCamera::PlayerCamera(int width, int height) : screen_width(width), screen_height(height)
{
    camera.target = { 0, 0 };
    camera.offset = { screen_width / 2.0f, screen_height/ 2.0f };
    camera.zoom = 2.0f;
    camera.rotation = 0.0f;
}

Camera2D& PlayerCamera::GetCamera()
{
    return camera;
}