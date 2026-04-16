#define CUTE_TILED_IMPLEMENTATION
#include "include/cute_tiled.h"

#include "include/map.hpp"

void TileMap::Load(const std::string& tmx_path)
{
    map = cute_tiled_load_map_from_file(tmx_path.c_str(), NULL);
    if (!map) {
        TraceLog(LOG_ERROR, "FAILED to parse TMX: %s", tmx_path.c_str());
        return;
    }
    TraceLog(LOG_INFO, "Map loaded: %dx%d tiles", map->width, map->height);

    std::string map_dir = tmx_path.substr(0, tmx_path.find_last_of("/\\") + 1);
    tile_width = map->tilewidth;
    tile_height = map->tileheight;

    cute_tiled_tileset_t* ts = map->tilesets;
    int count = 0;
    while (ts) {
        count++;
        TraceLog(LOG_INFO, "Tileset #%d: firstgid=%d", count, ts->firstgid);

        if (ts->image.ptr) {
            TraceLog(LOG_INFO, "  image: %s", ts->image.ptr);
        }
        else {
            TraceLog(LOG_WARNING, "  image is NULL!");
        }

        if (ts->image.ptr) {
            std::string img_path = map_dir + std::string(ts->image.ptr);
            TraceLog(LOG_INFO, "  full path: %s", img_path.c_str());

            Texture2D tex = LoadTexture(img_path.c_str());
            if (tex.id == 0)
                TraceLog(LOG_ERROR, "  FAILED to load texture!");
            else
                TraceLog(LOG_INFO, "  Loaded! %dx%d", tex.width, tex.height);

            int cols = tex.width / tile_width;
            tilesets.push_back({ tex, ts->firstgid, cols, tile_width });
        }

        ts = ts->next;
    }
    cute_tiled_layer_t* layer = map->layers;
    while (layer)
    {
        if (layer->objects)
        {
            cute_tiled_object_t* obj = layer->objects;
            while (obj)
            {
                colliders.push_back({
                    (float)obj->x,
                    (float)obj->y,
                    (float)obj->width,
                    (float)obj->height
                    });
                obj = obj->next;
            }
        }
        layer = layer->next;
    }

    TraceLog(LOG_INFO, "Total tilesets found: %d", count);
}
void TileMap::DrawDebugColliders()
{
    for (auto& col : colliders) {
        DrawRectangleLinesEx(col, 1, RED);
    }
}
bool TileMap::IsColliding(Rectangle rect)
{
    for (auto& col : colliders)
        if (CheckCollisionRecs(rect, col))
            return true;
    return false;
}


TilesetInfo* TileMap::GetTileset(int tile_id)
{
    TilesetInfo* result = nullptr;
    for (auto& ts : tilesets) {
        if (tile_id >= ts.firstgid) {
            if (!result || ts.firstgid > result->firstgid)
                result = &ts;
        }
    }
    return result;
}

void TileMap::Update()
{
    // Animation 
}

void TileMap::Draw()
{
    if (!map) return;

    cute_tiled_layer_t* layer = map->layers;
    while (layer) {
        if (layer->data_count > 0) {

            float parallax_x = layer->parallaxx; // cute_tiled parses these
            float parallax_y = layer->parallaxy;

            for (int i = 0; i < layer->data_count; i++) {
                int tile_id = layer->data[i];
                if (tile_id <= 0) continue;
                TilesetInfo* ts = GetTileset(tile_id);
                if (!ts) continue;
                if (ts->columns <= 0) continue;

                int local_id = tile_id - ts->firstgid;
                int src_x = (local_id % ts->columns) * tile_width;
                int src_y = (local_id / ts->columns) * tile_height;

                int map_x = (i % map->width) * tile_width;
                int map_y = (i / map->width) * tile_height;

                // parallax offset relative to camera
                float offset_x = camera_x * (1.0f - parallax_x);
                float offset_y = camera_y * (1.0f - parallax_y);

                Rectangle src = { (float)src_x, (float)src_y,
                                  (float)tile_width, (float)tile_height };
                Vector2 pos = { (float)map_x - offset_x, (float)map_y - offset_y };
                DrawTextureRec(ts->texture, src, pos, WHITE);
            }
        }
        layer = layer->next;
    }
}

void TileMap::Unload()
{
    if (map) {
        cute_tiled_free_map(map);
        map = nullptr;
    }
    for (auto& ts : tilesets)
        UnloadTexture(ts.texture);
    tilesets.clear();
}