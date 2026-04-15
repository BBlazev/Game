#include "include/enemy.hpp"

void Enemy::InitEnemy()
{
    animations[AnimState::IDLE] = LoadTexture("assets/world/Characters/Skeleton 1/no shield/Skeleton 1 - animations-idle.png");
    animations[AnimState::WALK] = LoadTexture("assets/world/Characters/Skeleton 1/no shield/Skeleton 1 - animations-walk.png");
    animations[AnimState::ATTACK] = LoadTexture("assets/world/Characters/Skeleton 1/no shield/Skeleton 1 - animations-atk 1.png");

    frame_counts[AnimState::IDLE] = 8;
    frame_counts[AnimState::WALK] = 8;
    frame_counts[AnimState::ATTACK] = 18;

    Texture2D tex = animations[AnimState::IDLE];
    frame_rec = { 0, 0, (float)tex.width / 8, (float)tex.height };
}


void Enemy::UpdateFrame()
{
    Texture2D tex = animations[anim_state];
    int total = frame_counts[anim_state];
    float fw = (float)tex.width / total;

    frame_counter++;
    if (frame_counter >= (60 / frame_speed))
    {
        frame_counter = 0;
        current_frame++;
        if (current_frame >= total)
        {
            current_frame = 0;
            if (is_atacking)
            {
                is_atacking = false;
                frame_speed = FRAME_SPEED;
                SetAnimation(AnimState::IDLE);
            }
        }
    }

    frame_rec.width = fw;
    frame_rec.x = (float)current_frame * fw;
}
void Enemy::Draw()
{
    Texture2D tex = animations[anim_state];
    float scale = 1.2f;
    float w = frame_rec.width * scale;
    float h = frame_rec.height * scale;

    Rectangle source = frame_rec;
    if (direction == Direction::LEFT)
        source.width = -frame_rec.width;

    Rectangle dest = { position.x, position.y, w, h };
    Vector2 origin = { w / 2.0f, h / 2.0f };
    DrawTexturePro(tex, source, dest, origin, 0.0f, WHITE);
}

void Enemy::SetAnimation(AnimState new_state)
{
    if (anim_state != new_state)
    {
        anim_state = new_state;
        current_frame = 0;
        frame_counter = 0;
    }
}

void Enemy::UpdateEnemyPosition(Player& player, TileMap& map)
{
    Vector2 enemy_center = GetCenter();
    Vector2 player_center = player.GetCenter();
    float dx = player_center.x - enemy_center.x;
    float dy = player_center.y - enemy_center.y;
    float distance = sqrtf(dx * dx + dy * dy);

    if (distance < detect_range && distance > attack_range)
    {
        float nx = dx / distance;
        float ny = dy / distance;

        Vector2 new_pos = position;
        new_pos.x += nx * speed;
        new_pos.y += ny * speed;

        Rectangle full_rect = { new_pos.x - 10, new_pos.y + 25, 20, 16 };

        if (!map.IsColliding(full_rect))
        {
            position = new_pos;
        }
        else
        {
            Rectangle rect_x = { new_pos.x - 10, position.y + 25, 20, 16 };
            if (!map.IsColliding(rect_x))
                position.x = new_pos.x;

            Rectangle rect_y = { position.x - 10, new_pos.y + 25, 20, 16 };
            if (!map.IsColliding(rect_y))
                position.y = new_pos.y;
        }

        direction = (dx > 0) ? Direction::RIGHT : Direction::LEFT;
        SetAnimation(AnimState::WALK);
    }
    else if (distance <= attack_range)
    {
        SetAnimation(AnimState::ATTACK);
        frame_speed = ATTACK_FRAME_SPEED;
        is_atacking = true;

    }
    else
    {
        SetAnimation(AnimState::IDLE);
    }
}


