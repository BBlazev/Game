#pragma once

#include <memory>


#include "types.hpp"
#include "map.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "camera.hpp"
#include "screen.hpp"

class Game
{
public:
	void InitGame();
	void UpdateFrames();
	void HandleMovement();
	void UnloadAll();
	void Run();
	void DrawUI();

private:

	Player player;
	Enemy enemy;
	TileMap map;
	PlayerCamera camera;
};