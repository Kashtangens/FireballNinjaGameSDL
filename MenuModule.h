#ifndef MENU_MODULE_H
#define MENU_MODULE_H

#include "ShopModule.h"
#include "MapEditorModule.h"
#include <vector>

enum MenuState
{
    MainMenu, Settings, SkinShop, MapEditor, InGameMenu,
    MultiOrSinglePlayerSelector,
    MapSelector,
    SinglePlayerState,
};


class MenuManager
{
public:   
    static bool isExit;

    static void initMenusUIElements(DrawableListClass *drawableList, EventListenersListClass *eventListenersList, Window *wnd, MapManager *mapManager);

    static void setMenuState(MenuState menuState);

    static void closeMenuUIElements();

    static void menuIteration(DrawableListClass *drawableList, EventListenersListClass *eventListenersList, Window *wnd, MapManager *mapManager);

private:
    static MenuState state;
    static MenuState lastState;
    static std::vector<UiButton*> buttons;
};

// События кнопок главного меню 
void playButtonOnClick(UiButton *sender);

void mapEditorButtonOnClick(UiButton *sender);

void skinShopButtonOnClick(UiButton *sender);

void settingsButtonOnClick(UiButton *sender);

void exitButtonOnClick(UiButton *sender);

void backButtonOnClick(UiButton *sender);

void inputModeButtonOnClick(UiButton *sender);

void exitSinglePlayerOnClick(UiButton *sender);

#endif