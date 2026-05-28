#include "include/player.hpp"
#include <iostream>
#include <algorithm>
#include "raylib.h"


void Player::InitPlayer()
{
    for (int i = 1; i <= 14; i++)
        animations[AnimState::IDLE].push_back(
            LoadTexture(TextFormat("assets/player/NightLord/Idle/Idle%d.png", i)));

    for (int i = 1; i <= 10; i++)
        animations[AnimState::RUN].push_back(
            LoadTexture(TextFormat("assets/player/NightLord/Running/Running%d.png", i)));

    for (int i = 1; i <= 25; i++)
        animations[AnimState::ATTACK].push_back(
            LoadTexture(TextFormat("assets/player/NightLord/Attacks/LightAtkCombo/LightAtk%d.png", i)));

    for (int i = 1; i <= 4; i++)
        animations[AnimState::DASH].push_back(
            LoadTexture(TextFormat("assets/player/NightLord/Dashing/Dashing%d.png", i)));

}


void Player::UpdateFrame(float delta)
{
    auto& frames = animations[anim_state];
    frame_timer += delta;
    
    if (frame_timer >= (1.0f / frame_speed))
    {
        frame_timer = 0;
        current_frame++;
        if (current_frame >= (int)frames.size()) 
        {
            current_frame = 0;
            if (is_attacking)
            {
                is_attacking = false;
                frame_speed = FRAME_SPEED;
                SetAnimation(AnimState::IDLE);
            }
            else if (is_dashing)
            {
                is_dashing = false;
                frame_speed = FRAME_SPEED;
                SetAnimation(AnimState::IDLE);
            }
        }
    }
}

void Player::Draw()
{
    Texture2D tex = animations[anim_state][current_frame];
    float scale = 1.2f;
    float w = (float)tex.width * scale;
    float h = (float)tex.height * scale;

    Rectangle source = { 0, 0, (float)tex.width, (float)tex.height };
    if (direction == Direction::LEFT)
        source.width = -(float)tex.width;

    Rectangle dest = { position.x, position.y, w, h };
    DrawTexturePro(tex, source, dest, { 0, 0 }, 0.0f, WHITE);
}

void Player::SetAnimation(AnimState new_state)
{
    if (anim_state != new_state)
    {
        anim_state = new_state;
        current_frame = 0;
        frame_timer = 0;
    }
}



int Player::GetCurrentHealth() const
{
    return current_health;
}

int Player::GetMaxHealth() const 
{
    return max_health;
}

void Player::ReduceHealth(int dmg)
{
    current_health = std::clamp(current_health - dmg, min_health, max_health);
    //if(current_health == min_health)
        //dead
    std::cout << GetCurrentHealth() << std::endl;
}

void Player::AddHealth(int hp)
{
    current_health = std::clamp(current_health + hp, min_health, max_health);
    std::cout << GetCurrentHealth() << std::endl;

}
