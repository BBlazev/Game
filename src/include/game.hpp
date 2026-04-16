#pragma once

#include "types.hpp"
#include "map.hpp"
#include "enemy.hpp"
#include "player.hpp"


void InitGame(Player& player, Enemy& enemy, TileMap& map)
{
	map.Load("assets/world/map.json");
	player.InitPlayer();
	enemy.InitEnemy();

}

//
//void UpdateFrames(Player& player, Enemy& enemy)
//{
//    player.UpdateFrame();
//    enemy.UpdateFrame();
//}
//
//void HandleMovement(Player& player, TileMap& map)
//{
//    if (player.is_attacking)
//        return;
//    float speed = 2.0f;
//    Vector2 new_pos = player.position;
//    Rectangle player_rect = { new_pos.x + 64, new_pos.y + 90, 28, 8 };
//
//    if (player.is_dashing)
//    {
//        float dash_speed = 8.0f;
//        Vector2 new_pos = player.position;
//        new_pos.x += player.dash_direction.x * dash_speed;
//        new_pos.y += player.dash_direction.y * dash_speed;
//
//        Rectangle player_rect = { new_pos.x + 64, new_pos.y + 90, 28, 8 };
//        if (!map.IsColliding(player_rect)) {
//            player.position = new_pos;
//        }
//        else {
//            player.is_dashing = false;
//            player.frame_speed = FRAME_SPEED;
//            player.SetAnimation(AnimState::IDLE);
//        }
//        return;
//    }
//
//
//
//
//    if (IsKeyDown(KEY_D))
//    {
//
//        new_pos.x += speed;
//        player.direction = Direction::RIGHT;
//
//    }
//    if (IsKeyDown(KEY_A))
//    {
//        new_pos.x -= speed;
//        player.direction = Direction::LEFT;
//
//    }
//    if (IsKeyDown(KEY_S))
//    {
//        new_pos.y += speed;
//    }
//    if (IsKeyDown(KEY_W))
//    {
//        new_pos.y -= speed;
//    }
//
//
//    if (!map.IsColliding(player_rect)) {
//        player.position = new_pos;
//    }
//    else {
//        Rectangle rect_x = { new_pos.x + 64, player.position.y + 90, 28, 8 };
//        if (!map.IsColliding(rect_x))
//            player.position.x = new_pos.x;
//
//        Rectangle rect_y = { player.position.x + 64, new_pos.y + 90, 28, 8 };
//        if (!map.IsColliding(rect_y))
//            player.position.y = new_pos.y;
//    }
//
//    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
//    {
//        player.SetAnimation(AnimState::ATTACK);
//        player.frame_speed = ATTACK_FRAME_SPEED;
//        player.is_attacking = true;
//    }
//    else if (IsKeyDown(KEY_SPACE))
//    {
//        player.SetAnimation(AnimState::DASH);
//        player.frame_speed = DASHING_FRAME_SPEED;
//        player.is_dashing = true;
//        player.dash_direction = { 0, 0 };
//        if (IsKeyDown(KEY_D)) player.dash_direction.x = 1;
//        if (IsKeyDown(KEY_A)) player.dash_direction.x = -1;
//        if (IsKeyDown(KEY_S)) player.dash_direction.y = 1;
//        if (IsKeyDown(KEY_W)) player.dash_direction.y = -1;
//
//        if (player.dash_direction.x == 0 && player.dash_direction.y == 0)
//            player.dash_direction.x = (player.direction == Direction::RIGHT) ? 1 : -1;
//    }
//    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_W))
//        player.SetAnimation(AnimState::RUN);
//    else
//        player.SetAnimation(AnimState::IDLE);
//
//}