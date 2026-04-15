#pragma once

#include "raylib.h"
#include "types.hpp"
#include "player.hpp"
#include "map.hpp"

#include <unordered_map>
#include <vector>

#define FRAME_SPEED  6
#define ATTACK_FRAME_SPEED 6
#define DASHING_FRAME_SPEED 7



class Enemy
{
public:

    void InitEnemy();
    void UpdateFrame();
    void Draw();
    void SetAnimation(AnimState new_state);
    void UpdateEnemyPosition(Player& player, TileMap& map);
    
    Vector2 GetCenter() { return { position.x, position.y + 20 }; }

    AnimState anim_state = AnimState::IDLE;
    Direction direction = Direction::RIGHT;
    Vector2 position = {600, 600};

    Rectangle frame_rec = { 0 };
    int total_frames = 8;

    std::unordered_map<AnimState, Texture2D> animations;
    int frame_speed = FRAME_SPEED;

private:

    float detect_range = 200.0f;
    float attack_range = 10.0f;
    float speed = 1.0f;

    int current_frame = 0;
    int frame_counter = 0;

};