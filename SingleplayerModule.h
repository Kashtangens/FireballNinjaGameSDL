#ifndef SINGLEPLAYER_MODULE_H
#define SINGLEPLAYER_MODULE_H

#include "GameEntities.h"
#include "MapEditorModule.h"
#include "PhysicsModule.h"

#include <vector>

namespace SinglePlayer
{

    static std::vector<Entity*> entities = std::vector<Entity*>();
    static Map *map;
    
    void StartLevel(DrawableListClass *drawableList, EventListenersListClass *eventListenersList, Window *wnd, MapManager* mapManager);

    void StopLevel();

    void ExitLevel();

    void PlayIteration(MapManager &MapManager);

}

#endif