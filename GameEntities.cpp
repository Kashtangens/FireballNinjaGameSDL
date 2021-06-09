#include "GameEntities.h"

// Entity
Entity::Entity()
{
    this->dx = 0;
    this->dy = 0;
    this->texturesCount = 0;
    this->textures = NULL;
    this->speed = 0;
    this->rect = ScalableRect();
}

Entity::Entity(const ScalableRect &rect, SDL_Texture **textures, int texturesCount, float speed, DrawableListClass *drawableList, EventListenersListClass *eventListenersList)
{
    this->rect = ScalableRect(rect);
    this->texturesCount = texturesCount;
    this->textures = textures;
    this->speed = speed;
    this->dx = 0;
    this->dy = 0;
    if (drawableList != NULL)
    {
        this->selfDrawable = drawableList->Add(this);
    }
    else
    {
        this->selfDrawable = NULL;
    }
    if (eventListenersList != NULL)
    {
        this->selfEventListener = eventListenersList->Add(this);
    }
    else
    {   
        this->selfEventListener = NULL;
    }
}

Entity::~Entity()
{
    for (int i = 0; i < texturesCount; i++)
    {
        SDL_DestroyTexture(this->textures[i]);
        this->textures[i]=NULL;
    }
    if (this->selfDrawable != NULL)
        ((DrawableListStruct*)(this->selfDrawable))->drawableObject = NULL;
    if (this->selfEventListener != NULL)
        ((EventListenersListStruct*)(this->selfEventListener))->eventListener = NULL;
}

void Entity::HandleEvent(SDL_Event &event)
{

}

void Entity::Draw(SDL_Renderer *renderer)
{
    if (this->textures != NULL)
        SDL_RenderCopy(renderer, this->textures[0], NULL, this->rect.GetRectPointer());
}

void Entity::PreMove(std::vector<Entity*> *entities, MapManager &mapManager, Map &map)
{

}

void Entity::Move(std::vector<Entity*> *entities, MapManager &mapManager, Map &map)
{
    this->rect.TranslateXY(this->step_dx, this->step_dy);
}

void Entity::ReactOnCollisionWithEntity(void* entity, char col_x, char col_y)
{
    
}

void Entity::ReactOnCollisionWithMap(char col_x, char col_y)
{
    if (col_x != 0)
    {
        this->step_dx = 0;
    }
    if (col_y != 0)
    {
        this->step_dy = 0;
    }
}

float Entity::GetDx()
{
    return this->step_dx;
}

float Entity::GetDy()
{
    return this->step_dy;
}

ScalableRect Entity::GetRect()
{
    return this->rect;
}

ScalableRect* Entity::GetRectPointer()
{
    return &this->rect;
}

// Fireball
Fireball::Fireball() : Entity()
{
    this->owner = NULL;
    this->mouseX = 0;
    this->mouseY = 0;
}

Fireball::Fireball(const ScalableRect &rect, SDL_Texture **textures, int texturesCount, float speed, DrawableListClass *drawableList, EventListenersListClass *eventListenersList) : Entity(rect, textures, texturesCount, speed, drawableList, eventListenersList)
{
    this->mouseX = 0;
    this->mouseY = 0;
}

Fireball::~Fireball()
{
    for (int i = 0; i < texturesCount; i++)
    {
        SDL_DestroyTexture(this->textures[i]);
        this->textures[i]=NULL;
    }
    if (this->selfDrawable != NULL)
        ((DrawableListStruct*)(this->selfDrawable))->drawableObject = NULL;
    if (this->selfEventListener != NULL)
        ((EventListenersListStruct*)(this->selfEventListener))->eventListener = NULL;
}

void Fireball::HandleEvent(SDL_Event &event)
{
    if (Info::inputType == Info::InputType::KeyboardOnly)
    {
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_UP:
                    this->dy -= speed;
                    break;
                case SDLK_DOWN:
                    this->dy += speed;
                    break;
                case SDLK_LEFT:
                    this->dx -= speed;
                    break;
                case SDLK_RIGHT:
                    this->dx += speed;
                    break;
            }
        }
        if (event.type == SDL_KEYUP && event.key.repeat == 0)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_UP:
                    this->dy += speed;
                    break;
                case SDLK_DOWN:
                    this->dy -= speed;
                    break;
                case SDLK_LEFT:
                    this->dx += speed;
                    break;
                case SDLK_RIGHT:
                    this->dx -= speed;
                    break;
            }
        }
    }   
    else if (Info::inputType == Info::InputType::KeyboardWithMouse)
    {
        SDL_GetMouseState(&mouseX, &mouseY);
        this->mouseX += Info::cameraX;
        this->mouseY += Info::cameraY;
    }
}

void Fireball::PreMove(std::vector<Entity*> *entities, MapManager &mapManager, Map &map)
{
    if (Info::inputType == Info::InputType::KeyboardWithMouse){
        // Рассчитываем направление к точке по прямой
        int distanceX = (mouseX - this->rect.GetRect().x);
        int distanceY = (mouseY - this->rect.GetRect().y);
        // printf("Camera: %d, %d\n", Info::cameraX, Info::cameraY);
        // printf("MouseX %d, MouseY %d\n", mouseX, mouseY);
        // printf("Fireball %d, %d\n", this->rect.GetRect().x, this->rect.GetRect().y);
        float distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));
        if (distance != 0)
        {
            this->dx = (distanceX / distance) * this->speed;
            this->dy = (distanceY / distance) * this->speed;
        }
        else 
        {
            this->dx = 0;
            this->dy = 0;
        }
    }
    this->step_dx = this->dx * TimeManager::GetDeltaTime();
    this->step_dy = this->dy * TimeManager::GetDeltaTime();
}

// void Fireball::Move(std::vector<Entity*> *entities, MapManager &mapManager, Map &map)
// {
//     float copy_dx = this->dx * TimeManager::GetDeltaTime();
//     float copy_dy = this->dy * TimeManager::GetDeltaTime();
//     // CheckMapCollision(this->rect.GetRect(), copy_dx, copy_dy, mapManager, map);
//     // printf("After checkCollision dx: %f, dy: %f\n", copy_dx, copy_dy);
//     this->rect.TranslateXY(copy_dx, copy_dy);
// }

void Fireball::ReactOnCollisionWithMap(char col_x, char col_y)
{
    float x = this->owner->GetRect().GetStartRect().x;
    float y = this->owner->GetRect().GetStartRect().y;
    this->rect.SetXY(x, y);
}


void Fireball::SetOwner(Entity* owner)
{
    this->owner = owner;
}


// Player
Player::Player() : Entity()
{
    this->hp = 0;
    this->fireball = NULL;
}

Player::Player(const ScalableRect &rect, SDL_Texture **textures, int texturesCount, float speed, DrawableListClass *drawableList, EventListenersListClass *eventListenersList, int hp, Fireball *fireball) : Entity(rect, textures, texturesCount, speed, drawableList, eventListenersList)
{
    this->hp = hp;
    this->fireball = fireball;
    this->fireball->SetOwner(this);
}

Player::~Player()
{
    delete this->fireball;
    for (int i = 0; i < texturesCount; i++)
    {
        SDL_DestroyTexture(this->textures[i]);
        this->textures[i]=NULL;
    }
    if (this->selfDrawable != NULL)
        ((DrawableListStruct*)(this->selfDrawable))->drawableObject = NULL;
    if (this->selfEventListener != NULL)
        ((EventListenersListStruct*)(this->selfEventListener))->eventListener = NULL;
}

void Player::HandleEvent(SDL_Event &event)
{
    if (Info::inputType == Info::InputType::KeyboardOnly || Info::inputType == Info::InputType::KeyboardWithMouse)
    {
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_w:
                    this->dy -= speed;
                    break;
                case SDLK_s:
                    this->dy += speed;
                    break;
                case SDLK_a:
                    this->dx -= speed;
                    break;
                case SDLK_d:
                    this->dx += speed;
                    break;
            }
        }
        if (event.type == SDL_KEYUP && event.key.repeat == 0)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_w:
                    this->dy += speed;
                    break;
                case SDLK_s:
                    this->dy -= speed;
                    break;
                case SDLK_a:
                    this->dx += speed;
                    break;
                case SDLK_d:
                    this->dx -= speed;
                    break;
            }
        }
    }   
}

void Player::PreMove(std::vector<Entity*> *entities, MapManager &mapManager, Map &map)
{
    this->step_dx = this->dx * TimeManager::GetDeltaTime();
    this->step_dy = this->dy * TimeManager::GetDeltaTime();
}

// void Player::Move(std::vector<Entity*> *entities)
// {
//     this->rect.TranslateXY(this->dx * TimeManager::GetDeltaTime(), this->dy * TimeManager::GetDeltaTime());
// }
