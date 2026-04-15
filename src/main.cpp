#include "raylib.h"

#include "include/player.hpp"
#include "include/enemy.hpp"
#include "include/screen.hpp"
#include "include/map.hpp"
#include <print>




void UpdateFrames(Player& player, Enemy& enemy)
{
    player.UpdateFrame();
    enemy.UpdateFrame();
}

void HandleMovement(Player& player, TileMap& map)
{
    if (player.is_attacking)
        return;
    float speed = 2.0f;
    Vector2 new_pos = player.position;
    Rectangle player_rect = { new_pos.x + 64, new_pos.y + 90, 28, 8 };

    if (player.is_dashing)
    {
        float dash_speed = 8.0f;
        Vector2 new_pos = player.position;
        new_pos.x += player.dash_direction.x * dash_speed;
        new_pos.y += player.dash_direction.y * dash_speed;

        Rectangle player_rect = { new_pos.x + 64, new_pos.y + 90, 28, 8 };
        if (!map.IsColliding(player_rect)) {
            player.position = new_pos;
        }
        else {
            player.is_dashing = false;
            player.frame_speed = FRAME_SPEED;
            player.SetAnimation(AnimState::IDLE);
        }
        return;
    }




    if (IsKeyDown(KEY_D)) 
    {

        new_pos.x += speed;
        player.direction = Direction::RIGHT;

    }
    if (IsKeyDown(KEY_A)) 
    {
        new_pos.x -= speed;
        player.direction = Direction::LEFT;

    }
    if (IsKeyDown(KEY_S)) 
    {
        new_pos.y += speed;
    }
    if (IsKeyDown(KEY_W)) 
    {
        new_pos.y -= speed;
    }
    

    if (!map.IsColliding(player_rect)) {
        player.position = new_pos;
    }
    else {
        Rectangle rect_x = { new_pos.x + 64, player.position.y + 90, 28, 8 };
        if (!map.IsColliding(rect_x))
            player.position.x = new_pos.x;

        Rectangle rect_y = { player.position.x + 64, new_pos.y + 90, 28, 8 };
        if (!map.IsColliding(rect_y))
            player.position.y = new_pos.y;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        player.SetAnimation(AnimState::ATTACK);
        player.frame_speed = ATTACK_FRAME_SPEED;
        player.is_attacking = true;
    }
    else if (IsKeyDown(KEY_SPACE))
    {
        player.SetAnimation(AnimState::DASH);
        player.frame_speed = DASHING_FRAME_SPEED;
        player.is_dashing = true;
        player.dash_direction = { 0, 0 };
        if (IsKeyDown(KEY_D)) player.dash_direction.x = 1;
        if (IsKeyDown(KEY_A)) player.dash_direction.x = -1;
        if (IsKeyDown(KEY_S)) player.dash_direction.y = 1;
        if (IsKeyDown(KEY_W)) player.dash_direction.y = -1;

        if (player.dash_direction.x == 0 && player.dash_direction.y == 0)
            player.dash_direction.x = (player.direction == Direction::RIGHT) ? 1 : -1;
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_W)) 
        player.SetAnimation(AnimState::RUN);
    else 
        player.SetAnimation(AnimState::IDLE);
    
}

int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RPG game");
    SetTargetFPS(120);

    TileMap map;
    map.Load("assets/world/map.json");

    Player player;
    player.InitPlayer();

    Enemy enemy;
    enemy.InitEnemy();

    Camera2D camera = { 0 };
    camera.target = { 0, 0 };
    camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.zoom = 2.0f; 
    camera.rotation = 0.0f;
    Color shadowColor = { 0, 0, 0, 80 };



    while (!WindowShouldClose()) {
        camera.target = { player.position.x, player.position.y };
        HandleMovement(player, map);

        map.Update();
        UpdateFrames(player, enemy);
        enemy.UpdateEnemyPosition(player, map);


        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera);
                map.Draw();
                map.DrawDebugColliders();
                player.Draw();
                enemy.Draw();
                DrawRectangle(enemy.position.x - 10, enemy.position.y + 25, 20, 16, RAYWHITE);
                EndMode2D();
        EndDrawing();
    }

    for (auto& anim : player.animations)
        for (auto& texture : anim.second)
            UnloadTexture(texture);
    map.Unload();

    CloseWindow();
    return 0;
}

