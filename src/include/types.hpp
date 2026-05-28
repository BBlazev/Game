#pragma once


constexpr float BASE_MOVEMENT_SPEED_PLAYER = 240.0f;
constexpr float BASE_MOVEMENT_SPEED_ENEMY = 100.0f;
constexpr float DASH_SPEED = 800.0f;

constexpr float ENEMY_AA_DETECT_RANGE = 200.0f;
constexpr float ENEMY_AA_RANGE = 30.0f;

constexpr int FRAME_SPEED = 10;
constexpr int ATTACK_FRAME_SPEED = 12;
constexpr int DASHING_FRAME_SPEED = 10;

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