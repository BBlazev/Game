#pragma once
#include "raylib.h"
#include "cute_tiled.h"
#include <vector>
#include <string>
#include <unordered_map>

struct TilesetInfo 
{
    Texture2D texture;
    int firstgid;
    int columns;
    int tile_size;
};

class TileMap 
{
public:

    void Load(const std::string& tmx_path);
    void Update();
    void Draw();
    void Unload();
    int GetTilesetCount() { return (int)tilesets.size(); }
    void DrawDebugColliders();

    bool IsColliding(Rectangle rect);
    std::vector<Rectangle> colliders;
private:

    std::vector<TilesetInfo> tilesets;
    cute_tiled_map_t* map = nullptr;
    int tile_width;
    int tile_height;
    TilesetInfo* GetTileset(int tile_id);
};