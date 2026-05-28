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
	void UpdateFrames(float delta);
	void HandleMovement(float delta);
	void UnloadAll();
	void Run();
	void DrawUI();

private:

	bool toggle_debug = false;
	float update_ms = 0.0f;
	float render_ms = 0.0f;
	Player player;
	Enemy enemy;
	TileMap map;
	PlayerCamera camera;
};