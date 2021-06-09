#ifndef INIT_MODULE_H
#define INIT_MODULE_H

// Инклудим библиотеки sdl в условии, чтобы они не дублировались
#ifndef SDL_INCLUDES
#define SDL_INCLUDES

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

#include "MenuModule.h"

bool init(Window &wnd)
{
    // Инициализируем SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Init SDL_Init. SDL Error: %s\n", SDL_GetError());
        return false;
    }
    // Создаем и инициализируем окно
    wnd = Window();
    if (!wnd.Init("FireballNinja"))
    {
        printf("Init Window. SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Инициализируем пакет для загрузки png изображений
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf("Init IMG_Init. SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool close(Window &wnd)
{
    wnd.~Window();
    MenuManager::closeMenuUIElements();
    IMG_Quit();
    SDL_Quit();
    return true;
}


#endif