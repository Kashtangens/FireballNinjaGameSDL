#include "PhysicsModule.h"

void CheckMapCollision(Entity *entity1, MapManager &mapManager, Map &map)
{
    int mathTileSize = mapManager.GetTilesRect().GetRect().h;
    // printf("y %d, x %d\n", int(entityCollider.y+5)/mathTileSize, int(entityCollider.x + entityCollider.w + dx)/mathTileSize);
    SDL_Rect entityCollider = entity1->GetRect().GetRect();
    if (entity1->GetDx() > 0)
    {
        int my_map_x = int(entityCollider.x + entityCollider.w + entity1->GetDx())/mathTileSize;
        int my_map_y_h = int(entityCollider.y+entityCollider.h-5)/mathTileSize;
        int my_map_y = int(entityCollider.y+5)/mathTileSize;
        if (map.tiles[1][my_map_y][my_map_x] > -1)
        {
            if (mapManager.GetTileType(map.tiles[1][my_map_y][my_map_x]+mapManager.GetTilesCount()) == TileType::Object)
            {
                entity1->ReactOnCollisionWithMap(1, 0);
            }
        }
        else if (map.tiles[1][my_map_y_h][my_map_x] > -1)
        {
            if (mapManager.GetTileType(map.tiles[1][my_map_y_h][my_map_x]+mapManager.GetTilesCount()) == TileType::Object)
            {
                entity1->ReactOnCollisionWithMap(1, 0);
            }
        }
    } 
    else if (entity1->GetDx() < 0)
    {
        int my_map_x = int(entityCollider.x+entity1->GetDx())/mathTileSize;
        int my_map_y_h = int(entityCollider.y+entityCollider.h-5)/mathTileSize;
        int my_map_y = int(entityCollider.y+5)/mathTileSize;
        if (map.tiles[1][my_map_y][my_map_x] > -1)
        {
            if (mapManager.GetTileType(map.tiles[1][my_map_y][my_map_x]+mapManager.GetTilesCount()) == TileType::Object)
            {
                entity1->ReactOnCollisionWithMap(-1, 0);
            }
        }
        else if (map.tiles[1][my_map_y_h][my_map_x] > -1)
        {
            if (mapManager.GetTileType(map.tiles[1][my_map_y_h][my_map_x]+mapManager.GetTilesCount()) == TileType::Object)
            {
                entity1->ReactOnCollisionWithMap(-1, 0); 
            }
        }
    }
    if (entity1->GetDy() > 0)
    {
        int my_map_x = int(entityCollider.x+5)/mathTileSize;
        int my_map_x_h = int(entityCollider.x+entityCollider.w-5)/mathTileSize;
        int my_map_y = int(entityCollider.y+entity1->GetDy()+entityCollider.h)/mathTileSize;
        if (map.tiles[1][my_map_y][my_map_x] > -1)
        {
            if (mapManager.GetTileType(map.tiles[1][my_map_y][my_map_x]+mapManager.GetTilesCount()) == TileType::Object)
            {
                entity1->ReactOnCollisionWithMap(0, 1); 
            }
        }
        else if (map.tiles[1][my_map_y][my_map_x_h] > -1)
        {
            if (mapManager.GetTileType(map.tiles[1][my_map_y][my_map_x_h]+mapManager.GetTilesCount()) == TileType::Object)
            {
                entity1->ReactOnCollisionWithMap(0, 1); 
            }
        }
    } 
    else if (entity1->GetDy() < 0)
    {
        int my_map_x = int(entityCollider.x+5)/mathTileSize;
        int my_map_x_h = int(entityCollider.x+entityCollider.w-5)/mathTileSize;
        int my_map_y = int(entityCollider.y+entity1->GetDy())/mathTileSize;
        if (map.tiles[1][my_map_y][my_map_x] > -1)
        {
            if (mapManager.GetTileType(map.tiles[1][my_map_y][my_map_x]+mapManager.GetTilesCount()) == TileType::Object)
            {
                entity1->ReactOnCollisionWithMap(0, -1); 
            }
        }
        else if (map.tiles[1][my_map_y][my_map_x_h] > -1)
        {
            if (mapManager.GetTileType(map.tiles[1][my_map_y][my_map_x_h]+mapManager.GetTilesCount()) == TileType::Object)
            {
                entity1->ReactOnCollisionWithMap(0, -1); 
            }
        }

    }
    // printf("In checkCollision dx: %f, dy: %f\n", dx, dy);
}

void CheckCollision(Entity* entity1, Entity* entity2)
{
    // // Проверку коллизий сделай, примерно как в карте, чтобы можно было направления указывать
    // if (entity1->GetRect().GetRect().y + entity1->GetRect().GetRect().h + entity1->GetDy() <= entity2->GetRect().GetRect().y + entity2->GetDy())
    // {
    //     return;
    // }
    // if (entity2->GetRect().GetRect().y + entity2->GetRect().GetRect().h + entity2->GetDy() <= entity1->GetRect().GetRect().y + entity2->GetDy())
    // {
    //     return;
    // }
    // if (entity1->GetRect().GetRect().x + entity1->GetRect().GetRect().w + entity1->GetDx() <= entity2->GetRect().GetRect().x + entity2->GetDx())
    // {
    //     return;
    // }
    // if (entity2->GetRect().GetRect().x + entity2->GetRect().GetRect().w + entity2->GetDx() <= entity1->GetRect().GetRect().x + entity1->GetDx())
    // {
    //     return;
    // }
    // printf("COLLISION\n");
    // entity1->ReactOnCollisionWithEntity(entity2, 1, 1);
    // entity2->ReactOnCollisionWithEntity(entity1, 1, 1);

}
//-------------------------------------------------------------------------------