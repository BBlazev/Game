#include "raylib.h"

#include "include/player.hpp"
#include "include/enemy.hpp"
#include "include/screen.hpp"
#include "include/map.hpp"
#include "include/game.hpp"
#include "include/camera.hpp"
#include <print>



int main() {

    //InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RPG game");
    //SetTargetFPS(120);

    Game game;

    //game.InitGame();

    game.Run();



    //game.UnloadAll();



    //CloseWindow();
    return 0;
}

