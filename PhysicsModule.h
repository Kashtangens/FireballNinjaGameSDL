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
void CheckCollision(SDL_Rect boxCollider1, float &dx, float &dy, SDL_Rect boxCollider2);

void CheckMapCollision(Entity* entity1, MapManager &MapManager, Map &map);

#endif