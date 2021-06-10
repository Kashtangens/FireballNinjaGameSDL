#ifndef MAP_EDITOR_MODULE_H
#define MAP_EDITOR_MODULE_H

#include "DrawingModule.h"
#include <vector>

#define tileSize 64

enum TileType
{
    DefaultTile,
    Spawner,
    Object
};

class Tile
{
public:
    Tile();

    Tile(ScalableRect &rect, SDL_Texture *texture, TileType tileType);

    ~Tile();

    void Draw(SDL_Renderer *renderer, int x, int y);

    TileType GetType();

private:
    TileType type;
    ScalableRect rect;
    SDL_Texture *texture;
};

// В этом классе будем инициализировать набор тайлов, получать к ним доступ
class MapManager
{
public:
    MapManager(Window* wnd);

    ~MapManager();

    void InitTiles();

    void DrawTile(int tileNumber, int x, int y);

    int GetTilesCount();

    ScalableRect GetTilesRect();

    TileType GetTileType(int tileNumber);

private:
    Tile **tiles;
    int tilesCount;
    ScalableRect tilesRect;
    SDL_Renderer *renderer;
};

class Map : Drawable
{
public:
    int ***tiles;
    int **player_path;
    int **fireball_path;

    Map();

    Map(int size_x, int size_y, DrawableListClass *drawableList, MapManager *mapManager);

    Map(int size_x, int size_y, int ***tiles, DrawableListClass *drawableList, MapManager *mapManager);

    ~Map();

    void RenderMapTexture();

    void Draw(SDL_Renderer *renderer);

    int GetMapWidth();

    int GetMapHeight();

    void ReloadPaths();

private:
    int size_x, size_y;
    SDL_Texture *mapTexture;
    MapManager *mapManager;
};


#endif