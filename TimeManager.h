#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#ifndef SDL_INCLUDES
#define SDL_INCLUDES

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

class TimeManager
{
public:
    static void InitStartTime();

    static void SetDeltaTime();

    static double GetDeltaTime();

private:
    static double startTime;
    static double deltaTime;
};

#endif