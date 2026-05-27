#pragma once

#include "raylib.h"
#include "types.hpp"
#include <vector>
#include <string>
#include <unordered_map>






class Player {

public:

    void InitPlayer();
    void UpdateFrame();
    void Draw();
    void SetAnimation(AnimState new_state);
    int GetCurrentHealth() const;
    int GetMaxHealth() const;
    void ReduceHealth(int dmg);
    void AddHealth(int dmg);
    Vector2 GetCenter() { return { position.x + 78, position.y + 64 }; }

    AnimState anim_state = AnimState::IDLE;
    Direction direction = Direction::RIGHT;
    Vector2 position = { 650.0f, 580.0f };
    Vector2 dash_direction = { 0,0 };
    bool is_moving{ false };
    bool is_attacking{ false };
    bool is_dashing{ false };

    std::unordered_map<AnimState, std::vector<Texture2D>> animations;
    int frame_speed = FRAME_SPEED;



private:
    int max_health = 100;
    int min_health = 0;
    int current_health = max_health;

    int current_frame = 0;
    int frame_counter = 0;
};