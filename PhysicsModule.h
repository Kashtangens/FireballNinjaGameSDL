#ifndef PHYSICS_MODULE_H
#define PHYSICS_MODULE_H

#ifndef SDL_INCLUDES
#define SDL_INCLUDES

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

#include "MapEditorModule.h"
#include "GameEntities.h"

// Система рассчета коллизий
void CheckCollision(Entity* entity1, Entity* entity2);

void CheckMapCollision(Entity* entity1, MapManager &MapManager, Map &map);

#endif