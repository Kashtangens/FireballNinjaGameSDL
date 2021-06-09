#include "MapEditorModule.h"

MapManager::MapManager(Window *wnd)
{
    this->tiles = NULL;
    this->renderer = wnd->renderer;
    this->tilesRect = ScalableRect(0, 0, tileSize, tileSize, wnd, SR_HorizontalAlignment_Left | SR_VerticalAlignment_Top);
    this->tilesCount = 0;
}

MapManager::~MapManager()
{
    // Допиши очистку памяти
    for (int i = 0; i < this->tilesCount; i++)
    {
        delete this->tiles[i];
    }
    
}

void MapManager::InitTiles()
{
    this->tilesCount = 1;
    this->tiles = new Tile*[2];
    this->tiles[0] = new Tile(this->tilesRect, loadTexture("textures/Tiles/Floor.png", this->renderer), TileType::DefaultTile);
    this->tiles[1] = new Tile(this->tilesRect, loadTexture("textures/Tiles/Wall.png", this->renderer), TileType::Object);
}

void MapManager::DrawTile(int tileNumber, int x, int y)
{
    this->tiles[tileNumber]->Draw(this->renderer, x, y);
}

int MapManager::GetTilesCount()
{
    return this->tilesCount;
}

TileType MapManager::GetTileType(int tileNumber)
{
    return this->tiles[tileNumber]->GetType();
}

ScalableRect MapManager::GetTilesRect()
{
    return this->tilesRect;
}

Tile::Tile()
{
    this->type = TileType::DefaultTile;
    this->texture = NULL;
    this->rect = ScalableRect();
}

Tile::Tile(ScalableRect &rect, SDL_Texture *texture, TileType tileType)
{
    this->type = tileType;
    this->rect = ScalableRect(rect);
    this->texture = texture;
}

Tile::~Tile()
{
    SDL_DestroyTexture(this->texture);
    this->texture = NULL;
}

void Tile::Draw(SDL_Renderer *renderer, int x, int y)
{
    if (this->texture != NULL)
    {
        this->rect.SetXY((float)(x*tileSize), (float)(y*tileSize));
        SDL_RenderCopy(renderer, this->texture, NULL, this->rect.GetRectPointer());
    }
}

TileType Tile::GetType()
{
    return this->type;
}

Map::Map()
{
    this->tiles = NULL;
    this->mapTexture = NULL;
    this->selfDrawable = NULL;
    this->size_x = 0;
    this->size_y = 0;
    this->mapManager = NULL;
}

Map::Map(int size_x, int size_y, DrawableListClass *drawableList, MapManager *mapManager)
{
    this->size_x = size_x;
    this->size_y = size_y;
    this->mapManager = mapManager;
    this->tiles = new int**[2];
    for (int j = 0; j < 2; j++)
    {
        this->tiles[j] = new int*[size_y];
        for (int i = 0; i < size_y; i++)
        {
            this->tiles[j][i] = new int[size_x];
        }
    }
    this->mapTexture = NULL;
    if (drawableList != NULL)
    {
        this->selfDrawable = drawableList->Add(this);
    }
    else
    {
        this->selfDrawable = NULL;
    }
}

Map::Map(int size_x, int size_y, int ***tiles, DrawableListClass *drawableList, MapManager *mapManager)
{
    printf("Start creating map object\n");
    this->size_x = size_x;
    this->size_y = size_y;
    this->tiles = tiles;
    this->mapManager = mapManager;
    this->mapTexture = NULL;
    if (drawableList != NULL)
    {
        this->selfDrawable = drawableList->Add(this);
    }
    else
    {
        this->selfDrawable = NULL;
    }
    printf("End creating map object\n");
}

Map::~Map()
{
    if (this->mapTexture != NULL)
    {
        SDL_DestroyTexture(this->mapTexture);
    }
    if (this->selfDrawable != NULL)
        ((DrawableListStruct*)(this->selfDrawable))->drawableObject = NULL;
}

void Map::RenderMapTexture()
{
    
}

void Map::Draw(SDL_Renderer *renderer)
{
    if (this->tiles != NULL){
        for (int i = 0; i < 2; i++)
        {
            for (int y = 0; y < this->size_y; y++)
            {
                for (int x = 0; x < this->size_x; x++)
                {
                    if (this->tiles[i][y][x] >= 0)
                    {
                        this->mapManager->DrawTile(this->tiles[i][y][x] + i*(this->mapManager->GetTilesCount()), x, y);
                    }
                }
            }
        }
    }
}

int Map::GetMapWidth()
{
    return this->size_x;
}

int Map::GetMapHeight()
{
    return this->size_y;
}

