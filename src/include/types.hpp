#pragma once

#define BASE_MOVEMENT_SPEED_PLAYER 2.0f;

enum class AnimState
{
    IDLE,
    RUN,
    WALK,
    ATTACK,
    DASH,
    DEATH
};

enum Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};