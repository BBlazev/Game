#pragma once

#include "raylib.h"
#include "types.hpp"
#include <vector>
#include <string>
#include <unordered_map>


#define FRAME_SPEED  6
#define ATTACK_FRAME_SPEED 6
#define DASHING_FRAME_SPEED 7



class Player {

public:

    void InitPlayer();
    void UpdateFrame();
    void Draw();
    void SetAnimation(AnimState new_state);
    Vector2 GetCenter() { return { position.x + 78, position.y + 64 }; }

    AnimState anim_state = AnimState::IDLE;
    Direction direction = Direction::RIGHT;
    Vector2 position = { 350.0f, 280.0f };
    Vector2 dash_direction = { 0,0 };
    bool is_moving{ false };
    bool is_attacking{ false };
    bool is_dashing{ false };

    std::unordered_map<AnimState, std::vector<Texture2D>> animations;
    int frame_speed = FRAME_SPEED;
private:

    int current_frame = 0;
    int frame_counter = 0;
};