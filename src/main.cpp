#include "raylib.h"

#include "include/player.hpp"
#include "include/enemy.hpp"
#include "include/screen.hpp"
#include "include/map.hpp"
#include "include/game.hpp"
#include "include/camera.hpp"
#include <print>



int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RPG game");
    SetTargetFPS(120);

    TileMap map;
    Player player;
    Enemy enemy;

    InitGame(player, enemy, map);

    PlayerCamera camera(SCREEN_WIDTH, SCREEN_HEIGHT);


    //Camera2D camera = { 0 };
    //camera.target = { 0, 0 };
    //camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    //camera.zoom = 2.0f; 
    //camera.rotation = 0.0f;



    while (!WindowShouldClose()) {
        camera.GetCamera().target = {player.position.x, player.position.y};
        HandleMovement(player, map);

        map.Update();
        UpdateFrames(player, enemy);
        enemy.UpdateEnemyPosition(player, map);
        Vector2 ec = enemy.GetCenter();

        Vector2 pc = player.GetCenter();
        map.camera_x = camera.GetCamera().target.x;
        map.camera_y = camera.GetCamera().target.y;
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera.GetCamera());
                map.Draw();
                map.DrawDebugColliders();
                player.Draw();
                enemy.Draw();

                EndMode2D();
        EndDrawing();
    }



    UnloadAll(player, map);



    CloseWindow();
    return 0;
}

