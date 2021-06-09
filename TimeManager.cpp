#include "TimeManager.h"

//TimeManager--------------------------------------------------------------------
double TimeManager::startTime = 0;
double TimeManager::deltaTime = 0;

void TimeManager::InitStartTime()
{
    TimeManager::startTime = ((double)SDL_GetTicks())/1000;
    if (TimeManager::startTime != TimeManager::startTime)
    {
        TimeManager::startTime = 0;
    }
}

void TimeManager::SetDeltaTime()
{
    TimeManager::deltaTime = ((double)SDL_GetTicks())/1000 - TimeManager::startTime;
    if (TimeManager::deltaTime != TimeManager::deltaTime)
    {
        TimeManager::deltaTime = 0;
    }
    TimeManager::startTime = ((double)SDL_GetTicks())/1000;
    if (TimeManager::startTime != TimeManager::startTime)
    {
        TimeManager::startTime = 0;
    }
}

double TimeManager::GetDeltaTime()
{
    if (TimeManager::deltaTime != TimeManager::deltaTime)
    {
        TimeManager::deltaTime = 0;
    }
    if (TimeManager::deltaTime < 0 || TimeManager::deltaTime > 1)
    {
        printf("deltaTime: %f, startTime: %f\n", TimeManager::deltaTime, TimeManager::startTime);
    }
    return TimeManager::deltaTime;
}