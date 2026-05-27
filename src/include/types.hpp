#pragma once


constexpr float BASE_MOVEMENT_SPEED_PLAYER = 2.0f;
constexpr int FRAME_SPEED = 6;
constexpr int ATTACK_FRAME_SPEED = 6;
constexpr int DASHING_FRAME_SPEED = 6;

enum class AnimState
{
    IDLE,
    RUN,
    WALK,
    ATTACK,
    DASH,
    DEATH
};

enum class Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};