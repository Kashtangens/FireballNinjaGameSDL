#include "InitModule.h"
#include "PhysicsModule.h"

void PrintHello();

int main()
{
    Window wnd;
    init(wnd);

    EventListenersListClass eventListeners = EventListenersListClass();
    DrawableListClass drawables = DrawableListClass();

    MapManager mapManager = MapManager(&wnd);
    mapManager.InitTiles();

    MenuManager::setMenuState(MenuState::MainMenu);
    MenuManager::initMenusUIElements(&drawables, &eventListeners, &wnd, &mapManager);

    TimeManager::InitStartTime();

    while (wnd.HandleAllEvents(eventListeners) != Window::WindowEvent::Close && !MenuManager::isExit)
    {
        TimeManager::SetDeltaTime();
        MenuManager::menuIteration(&drawables, &eventListeners, &wnd, &mapManager);
        wnd.RenderAll(drawables);
    }
    drawables.DeleteAll();
    eventListeners.DeleteAll();
    close(wnd);
    return 0;
}