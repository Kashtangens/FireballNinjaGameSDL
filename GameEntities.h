#ifndef GAME_ENTITIES_H
#define GAME_ENTITIES_H

#include "DrawingModule.h"
#include "InfoModule.h"
#include "MapEditorModule.h"
#include "TimeManager.h"
// #include "PhysicsModule.h"
#include <vector>
#include <queue>

enum EntityTypes {
    EntityType,
    FireballType,
    PlayerType,
    BotFireballType,
    BotPlayerType
};

enum BotStates
{
    Attack,
    Defence
};

class Entity: public EventListener, public Drawable
{
public:
    Entity();

    Entity(const ScalableRect &rect, SDL_Texture **textures, int texturesCount, float speed, DrawableListClass *drawableList, EventListenersListClass *eventListenersList);

    ~Entity();

    virtual void Draw(SDL_Renderer *renderer);

    virtual void HandleEvent(SDL_Event &event);

    virtual void PreMove(std::vector<Entity*> *entities, MapManager &mapManager, Map &map);

    virtual void Move(std::vector<Entity*> *entities, MapManager &mapManager, Map &map);

    ScalableRect GetRect();

    ScalableRect* GetRectPointer();

    virtual void ReactOnCollisionWithEntity(void* entity, char col_x, char col_y);

    virtual void ReactOnCollisionWithMap(char col_x, char col_y);

    float GetDx();

    float GetDy();

    EntityTypes GetType();

    int GetTeam();

protected:
    float dx, dy;
    float step_dx, step_dy;
    float speed;
    int texturesCount;
    SDL_Texture **textures;
    ScalableRect rect;
    int team;
    EntityTypes type;
};

class Fireball: public Entity
{
public:
    Fireball();

    Fireball(const ScalableRect &rect, SDL_Texture **textures, int textureCount, float speed, DrawableListClass *drawableList, EventListenersListClass *eventListenersList);

    ~Fireball();

    // virtual void Draw(SDL_Renderer *renderer);

    virtual void HandleEvent(SDL_Event &event);

    virtual void PreMove(std::vector<Entity*> *entities, MapManager &mapManager, Map &map);

    // virtual void Move(std::vector<Entity*> *entities, MapManager &mapManager, Map &map);

    // virtual void ReactOnCollisionWithEntity(void* entity, char col_x, char col_y);

    virtual void ReactOnCollisionWithMap(char col_x, char col_y);
    
    void SetOwner(Entity* owner);

private:
    int mouseX, mouseY;
    Entity* owner;
};

class Player: public Entity
{
public:
    Player();

    Player(const ScalableRect &rect, SDL_Texture **textures, int texturesCount, float speed, DrawableListClass *drawableList, EventListenersListClass *eventListenersList, int hp, Fireball *fireball);

    ~Player();

    // void Draw(SDL_Renderer *renderer);

    void HandleEvent(SDL_Event &event);

    virtual void PreMove(std::vector<Entity*> *entities, MapManager &mapManager, Map &map);

    // void Move(std::vector<Entity*> *entities);

    // virtual void ReactOnCollisionWithEntity(void* entity, char col_x, char col_y);

    // virtual void ReactOnCollisionWithMap(Tile &tile, char col_x, char col_y);

protected:
    int hp;
    Fireball *fireball;
};

class BotFireball: public Fireball
{
public:
    BotFireball();

    BotFireball(const ScalableRect &rect, SDL_Texture **textures, int textureCount, float speed, DrawableListClass *drawableList);

    virtual void PreMove(std::vector<Entity*> *entities, MapManager &mapManager, Map &map);
};

class BotPlayer: public Player
{
public:
    BotPlayer();

    BotPlayer(const ScalableRect &rect, SDL_Texture **textures, int texturesCount, float speed, DrawableListClass *drawableList, int hp, BotFireball *fireball);

    virtual void PreMove(std::vector<Entity*> *entities, MapManager &mapManager, Map &map);

    BotStates state;
};

#endif