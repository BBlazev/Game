#include "include/game.hpp"
#include <chrono>


void Game::InitGame()
{
    map.Load("assets/world/world.json");
    player.InitPlayer();
    enemy.InitEnemy();


}



void Game::UpdateFrames(float delta)
{
    player.UpdateFrame(delta);
    enemy.UpdateFrame(player, delta);
}

void Game::HandleMovement(float delta)
{
    if (player.is_attacking)
        return;

    Vector2 new_pos = player.position;
    Rectangle player_rect = { new_pos.x + 64, new_pos.y + 90, 28, 8 };

    if (player.is_dashing)
    {
        Vector2 new_pos = player.position;
        new_pos.x += player.dash_direction.x * DASH_SPEED * delta;
        new_pos.y += player.dash_direction.y * DASH_SPEED * delta;

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

        new_pos.x += BASE_MOVEMENT_SPEED_PLAYER * delta;
        player.direction = Direction::RIGHT;

    }
    if (IsKeyDown(KEY_A))
    {
        new_pos.x -= BASE_MOVEMENT_SPEED_PLAYER * delta;
        player.direction = Direction::LEFT;

    }
    if (IsKeyDown(KEY_S))
    {
        new_pos.y += BASE_MOVEMENT_SPEED_PLAYER * delta;
    }
    if (IsKeyDown(KEY_W))
    {
        new_pos.y -= BASE_MOVEMENT_SPEED_PLAYER * delta;
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

void Game::UnloadAll()
{
    for (auto& anim : player.animations)
        for (auto& texture : anim.second)
            UnloadTexture(texture);
    map.Unload();
}



void Game::Run()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RPG game");
    SetTargetFPS(240);
    InitGame();

    while (!WindowShouldClose()) {
        float delta =  GetFrameTime();
        camera.GetCamera().target = { player.position.x, player.position.y };
        if (IsKeyPressed(KEY_F3))
        {
            toggle_debug = !toggle_debug;
        }

        auto t0 = std::chrono::steady_clock::now();
        HandleMovement(delta);

        map.Update();
        UpdateFrames(delta);
        enemy.UpdateEnemyPosition(player, map, delta);
        Vector2 ec = enemy.GetCenter();

        Vector2 pc = player.GetCenter();
        map.camera_x = camera.GetCamera().target.x;
        map.camera_y = camera.GetCamera().target.y;
        
        auto t1 = std::chrono::steady_clock::now();
        update_ms = std::chrono::duration<float, std::milli>(t1 - t0).count();

        t0 = std::chrono::steady_clock::now();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        

        BeginMode2D(camera.GetCamera());
            map.Draw();
            map.DrawDebugColliders();
            player.Draw();
            enemy.Draw();
        EndMode2D();
        DrawUI();

        EndDrawing();

        t1 = std::chrono::steady_clock::now();
        render_ms = std::chrono::duration<float, std::milli>(t1 - t0).count();
    }
    UnloadAll();
    CloseWindow();

}

void Game::DrawUI()
{
    float ratio = static_cast<float>(player.GetCurrentHealth()) / player.GetMaxHealth();
    DrawRectangle(100, 100, 100, 20, WHITE);
    DrawRectangle(100, 100, 100 * ratio, 20, RED);
    
    
    if (toggle_debug){
        
        int fps = GetFPS();
        
        DrawText(TextFormat("FPS %d", fps), 1200, 50, 30, WHITE);
        DrawText(TextFormat("update: %.2f ms", update_ms), 1150, 110, 30, WHITE);
        DrawText(TextFormat("render: %.2f ms", render_ms), 1150, 160, 30, WHITE);


    }

}

