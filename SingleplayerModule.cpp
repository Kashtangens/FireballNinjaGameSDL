#include "SingleplayerModule.h"

void SinglePlayer::StartLevel(DrawableListClass *drawableList, EventListenersListClass *eventListenersList, Window *wnd, MapManager *mapManager)
{
    isGamePaused = false;
    // Создаем игрока
    ScalableRect fireballRect = ScalableRect(64, 64, 24, 24, wnd, SR_HorizontalAlignment_Left | SR_VerticalAlignment_Top);
    SDL_Texture **fireballTextures = new SDL_Texture*[1];
    fireballTextures[0] = loadTexture("textures/Entities/FireSprite.png", wnd->renderer);
    Fireball* fireball = new Fireball(fireballRect, fireballTextures, 1, 200, drawableList, eventListenersList);
    entities.push_back(fireball);
    ScalableRect playerRect = ScalableRect(64, 64, 30, 42, wnd, SR_HorizontalAlignment_Left | SR_VerticalAlignment_Top);
    SDL_Texture **playerTextures = new SDL_Texture*[1];
    playerTextures[0] = loadTexture("textures/Entities/PlayerSprite.png", wnd->renderer);
    Player* player = new Player(playerRect, playerTextures, 1, playerSpeedConstant, drawableList, eventListenersList, 100, fireball, 1);
    entities.push_back(player);
    // Создаем противников
    ScalableRect botFireballRect = ScalableRect(512, 64, 24, 24, wnd, SR_HorizontalAlignment_Left | SR_VerticalAlignment_Top);
    SDL_Texture **botFireballTextures = new SDL_Texture*[1];
    botFireballTextures[0] = loadTexture("textures/Entities/EnemyFireSprite.png", wnd->renderer);
    BotFireball* botFireball = new BotFireball(botFireballRect, botFireballTextures, 1, 200, drawableList);
    entities.push_back(botFireball);
    ScalableRect enemyRect = ScalableRect(512, 64, 30, 42, wnd, SR_HorizontalAlignment_Left | SR_VerticalAlignment_Top);
    SDL_Texture **enemyTextures = new SDL_Texture*[1];
    enemyTextures[0] = loadTexture("textures/Entities/EnemySprite.png", wnd->renderer);
    BotPlayer* enemy = new BotPlayer(enemyRect, enemyTextures, 1, playerSpeedConstant, drawableList, 100, botFireball, 2);
    entities.push_back(enemy);
    // Загружаем карту
    #define mapW 16
    #define mapH 16

    int tiles_demo[2][mapH][mapW] = 
    {
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0,-1,-1,-1,-1, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0},
            {0,-1,-1, 0,-1, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0},
            {0,-1,-1, 0,-1, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0},
            {0,-1,-1, 0, 0, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0},
            {0,-1,-1,-1,-1, 0,-1,-1,-1, 0, 0, 0,-1,-1,-1, 0},
            {0,-1,-1, 0, 0, 0,-1,-1,-1,-1,-1, 0,-1,-1,-1, 0},
            {0,-1,-1,-1,-1, 0,-1,-1,-1,-1,-1, 0,-1,-1,-1, 0},
            {0,-1,-1,-1,-1, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0},
            {0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0},
            {0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0},
            {0,-1,-1,-1,-1, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0},
            {0,-1,-1,-1,-1, 0, 0, 0, 0,-1,-1, 0,-1,-1,-1, 0},
            {0,-1,-1,-1,-1, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0},
            {0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        }
    };

    int ***tiles = new int**[2];
    for (int i = 0; i < 2; i++)
    {
        tiles[i] = new int*[mapH];
        for (int j = 0; j < mapH; j++)
        {
            tiles[i][j] = new int[mapW];
            for (int k = 0; k < mapW; k++)
            {
                tiles[i][j][k] = tiles_demo[i][j][k];
            }
        }
    }
    printf("Start creating map\n");
    map = new Map(mapW, mapH, tiles, drawableList, mapManager);
    // map->tilesRect = ScalableRect(0, 0, tileSize, tileSize, wnd, SR_HorizontalAlignment_Left | SR_VerticalAlignment_Top);
    printf("Created scene\n");
    // Устанавливаем камеру на игрока.
    wnd->camera.SetFollowableObject(player->GetRectPointer(), new ScalableRect(0, 0, map->GetMapWidth() * mapManager->GetTilesRect().GetStartRect().w, map->GetMapHeight() * mapManager->GetTilesRect().GetStartRect().h, wnd, SR_HorizontalAlignment_Left | SR_VerticalAlignment_Top));
}

void SinglePlayer::PlayIteration(MapManager &mapManager)
{
    if (!isGamePaused)
    {
        map->ReloadPaths();
        // Все продумывают свое перемещение
        for (auto entity = entities.begin(); entity != entities.end(); entity++)
        {
            (*entity)->PreMove(&entities, mapManager, *map);
        }
        //
        // Проверяем коллизии
        for (auto entity = entities.begin(); entity != entities.end(); entity++)
        {
            for (auto entity2 = entity + 1; entity2 != entities.end(); entity2++)
            {
                CheckCollision(*entity, *entity2);
            }
            CheckMapCollision(*entity, mapManager, *map);
            if ((*entity)->GetType() == PlayerType)
            {
                if (((Player*)(*entity))->GetHP() <= 0)
                {
                    isGamePaused = true;
                    return;
                }
            }
        }
        // Перемещаем 
        for (auto entity = entities.begin(); entity != entities.end(); entity++)
        {
            (*entity)->Move(&entities, mapManager, *map);
            printf("%d\n", (*entity)->GetTeam());
        }
    }
}

void SinglePlayer::ExitLevel()
{
    SinglePlayer::map->~Map();
    for (auto entity = SinglePlayer::entities.begin(); entity != SinglePlayer::entities.end(); entity++)
    {
        (**entity).~Entity();
    }
    SinglePlayer::entities.clear();
}