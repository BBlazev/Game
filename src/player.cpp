#include "include/player.hpp"

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

void Player::UpdateFrame()
{
    auto& frames = animations[anim_state];

    frame_counter++;
    if (frame_counter >= (60 / frame_speed))
    {
        frame_counter = 0;
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
        frame_counter = 0;
    }
}