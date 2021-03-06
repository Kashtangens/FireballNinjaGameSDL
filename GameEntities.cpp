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
    this->team = 0;
    this->type = EntityTypes::EntityType;
}

Entity::Entity(const ScalableRect &rect, SDL_Texture **textures, int texturesCount, float speed, DrawableListClass *drawableList, EventListenersListClass *eventListenersList, int team)
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
    this->team = team;
    this->type = EntityTypes::EntityType;
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

void Entity::ReactOnCollisionWithEntity(Entity* entity, char col_x, char col_y)
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

EntityTypes Entity::GetType()
{
    return this->type;
}

int Entity::GetTeam()
{
    return this->team;
}

// Fireball
Fireball::Fireball() : Entity()
{
    this->owner = NULL;
    this->mouseX = 0;
    this->mouseY = 0;
    this->type = EntityTypes::FireballType;
}

Fireball::Fireball(const ScalableRect &rect, SDL_Texture **textures, int texturesCount, float speed, DrawableListClass *drawableList, EventListenersListClass *eventListenersList) : Entity(rect, textures, texturesCount, speed, drawableList, eventListenersList, 0)
{
    this->mouseX = 0;
    this->mouseY = 0;
    this->type = EntityTypes::FireballType;
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
        // ???????????????????????? ?????????????????????? ?? ?????????? ???? ????????????
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

void Fireball::ReactOnCollisionWithEntity(Entity* entity, char col_x, char col_y)
{
    if (entity->GetTeam() != this->team)
    {
        float x = this->owner->GetRect().GetStartRect().x;
        float y = this->owner->GetRect().GetStartRect().y;
        this->rect.SetXY(x, y);
    }
}

void Fireball::ReactOnCollisionWithMap(char col_x, char col_y)
{
    float x = this->owner->GetRect().GetStartRect().x;
    float y = this->owner->GetRect().GetStartRect().y;
    this->rect.SetXY(x, y);
}


void Fireball::SetOwner(Entity* owner)
{
    this->owner = owner;
    this->team = owner->GetTeam();
}


// Player
Player::Player() : Entity()
{
    this->hp = 0;
    this->fireball = NULL;
    this->type = EntityTypes::PlayerType;
}

Player::Player(const ScalableRect &rect, SDL_Texture **textures, int texturesCount, float speed, DrawableListClass *drawableList, EventListenersListClass *eventListenersList, int hp, Fireball *fireball, int team) : Entity(rect, textures, texturesCount, speed, drawableList, eventListenersList, team)
{
    this->hp = hp;
    this->fireball = fireball;
    this->fireball->SetOwner(this);
    this->type = EntityTypes::PlayerType;
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
    // ?????????????? ?????????????? ????????------------------------------------
    // ???????????????? ?????????????????? ??????????
    int mathTileSize = mapManager.GetTilesRect().GetRect().h;
    SDL_Rect entityCollider = this->rect.GetRect();
    int my_map_x = int(entityCollider.x + entityCollider.w/2)/mathTileSize;
    int my_map_y = int(entityCollider.y + entityCollider.h/2)/mathTileSize;
    std::queue<SDL_Point> q;
    SDL_Point tmp = {my_map_x, my_map_y};
    SDL_Point observable_point;
    q.push(tmp);
    map.player_path[my_map_y][my_map_x] = 0;
    // ???????????????? ???? ???????? ??????????????????, ???????? ???????????? ?????? -1, ???? ????????????????????????????, ?????????? ???????? ???? ?????????????????? ?? ?????????????? 
    while (!q.empty())
    {
        tmp = q.front();
        q.pop();
        for (int i = tmp.y-1; i <= tmp.y+1; i++)
        {
            for (int j = tmp.x-1; j <= tmp.x+1; j++)
            {
                // ???????? ?????????? ???? ?????????????? ??????????
                if (i < 0 || j < 0 || i >= map.GetMapHeight() || j >= map.GetMapWidth())
                {
                    continue;
                }
                // ?????????? ???????????????? ??????????
                if ((map.player_path[i][j] > map.player_path[tmp.y][tmp.x]+1 || map.player_path[i][j] == -1) && (mapManager.GetTileType(map.tiles[1][i][j]+mapManager.GetTilesCount()) != TileType::Object))
                {
                    map.player_path[i][j] = map.player_path[tmp.y][tmp.x]+1;
                    observable_point.x = j;
                    observable_point.y = i;
                    q.push(observable_point);
                }
            }
        }
    }
    // --------------------------------------------------------
}

void Player::ReactOnCollisionWithEntity(Entity* entity, char col_x, char col_y)
{
    if (entity->GetType() != FireballType)
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
    else
    {
        if (entity->GetTeam() != this->team)
        {
            this->hp-=20;
        }
    }
}


// void Player::Move(std::vector<Entity*> *entities)
// {
//     this->rect.TranslateXY(this->dx * TimeManager::GetDeltaTime(), this->dy * TimeManager::GetDeltaTime());
// }

int Player::GetHP()
{
    return this->hp;
}

BotFireball::BotFireball() : Fireball() {}

BotFireball::BotFireball(const ScalableRect &rect, SDL_Texture **textures, int textureCount, float speed, DrawableListClass *drawableList) : Fireball(rect, textures, textureCount, speed, drawableList, NULL)
{

}

void BotFireball::PreMove(std::vector<Entity*> *entities, MapManager &mapManager, Map &map)
{
    // ???????????????? ???????? ???????????????????? ???? ?????????? ??????????
    int mathTileSize = mapManager.GetTilesRect().GetRect().h;
    SDL_Rect entityCollider = this->rect.GetRect();
    int my_map_x = int(entityCollider.x + entityCollider.w/2)/mathTileSize;
    int my_map_y = int(entityCollider.y+entityCollider.h/2)/mathTileSize;
    // ?????????????????????????? ?????????? ?????? ?????????????????????? ?? ?????????? ???????????? ?? ?????????????? ????????????
    int distanceX = 0;
    int distanceY = 0;
    bool isNearestFound = false;
    printf("BotFireballPosition %d %d\n", my_map_x, my_map_y);
    printf("%d, %d\n", map.player_path[my_map_y][my_map_x], mathTileSize);
    for (int i = my_map_y - 1; i <= my_map_y+1 && !isNearestFound; i++)
    {
        for (int j = my_map_x - 1; j <= my_map_x + 1 && !isNearestFound; j++)
        {
            if (i < 0 || j < 0 || i >= map.GetMapHeight() || j >= map.GetMapWidth() /*|| (i != my_map_y_h && j != my_map_y && j != my_map_x_w && j != my_map_x)*/)
            {
                continue;
            }
            if ((map.player_path[i][j] < map.player_path[my_map_y][my_map_x] && map.player_path[i][j] != -1) || (map.player_path[i][j] == 0))
            {
                printf("Nearest %d %d %d\n", i, j, map.player_path[i][j]);
                distanceX = j * mathTileSize + mathTileSize/2 - this->rect.GetRect().x - this->rect.GetRect().w/2;
                distanceY = i * mathTileSize + mathTileSize/2 - this->rect.GetRect().y - this->rect.GetRect().h/2;
                isNearestFound = true;
                printf("distance %d %d\n", distanceX, distanceY);
            }
        }
    }
    // if (!isNearestFound)
    // {
    //     distanceX
    //     distanceY
    // }
    // ???????????? dx ?? dy ?????? ?????????????????????? ?? ?????? ??????????
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
    this->step_dx = this->dx * TimeManager::GetDeltaTime();
    this->step_dy = this->dy * TimeManager::GetDeltaTime();
}

BotPlayer::BotPlayer() : Player() 
{
    // this->state = BotStates::Attack;
}

BotPlayer::BotPlayer(const ScalableRect &rect, SDL_Texture **textures, int texturesCount, float speed, DrawableListClass *drawableList, int hp, BotFireball *fireball, int team)/* : Player(rect, textures, texturesCount, speed, drawableList, NULL, hp, fireball)*/
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
    this->hp = hp;
    this->team = team;
    this->type = EntityTypes::PlayerType;
    this->fireball = fireball;
    this->fireball->SetOwner(this);
    // this->state = BotStates::Attack;
}

void BotPlayer::PreMove(std::vector<Entity*> *entities, MapManager &mapManager, Map &map)
{
    // ???????????????? ???????? ???????????????????? ???? ?????????? ??????????
    int mathTileSize = mapManager.GetTilesRect().GetRect().h;
    SDL_Rect entityCollider = this->rect.GetRect();
    int my_map_x = int(entityCollider.x + entityCollider.w/2)/mathTileSize;
    int my_map_y = int(entityCollider.y+entityCollider.h/2)/mathTileSize;
    // ?????????????????????????? ?????????? ?????? ?????????????????????? ?? ?????????? ???????????? ?? ?????????????? ????????????
    int distanceX = 0;
    int distanceY = 0;
    bool isNearestFound = false;
    printf("BotPlayerPosition %d %d\n", my_map_x, my_map_y);
    printf("%d, %d\n", map.player_path[my_map_y][my_map_x], mathTileSize);
    for (int i = my_map_y - 1; i <= my_map_y+1 && !isNearestFound && map.player_path[my_map_y][my_map_x] > 4; i++)
    {
        for (int j = my_map_x - 1; j <= my_map_x + 1 && !isNearestFound; j++)
        {
            if (i < 0 || j < 0 || i >= map.GetMapHeight() || j >= map.GetMapWidth() /*|| (i != my_map_y_h && j != my_map_y && j != my_map_x_w && j != my_map_x)*/)
            {
                continue;
            }
            if ((map.player_path[i][j] < map.player_path[my_map_y][my_map_x] && map.player_path[i][j] != -1))
            {
                printf("Nearest %d %d %d\n", i, j, map.player_path[i][j]);
                distanceX = j * mathTileSize + mathTileSize/2 - this->rect.GetRect().x - this->rect.GetRect().w/2;
                distanceY = i * mathTileSize + mathTileSize/2 - this->rect.GetRect().y - this->rect.GetRect().h/2;
                isNearestFound = true;
                printf("distance %d %d\n", distanceX, distanceY);
            }
        }
    }
    // if (!isNearestFound)
    // {
    //     distanceX
    //     distanceY
    // }
    // ???????????? dx ?? dy ?????? ?????????????????????? ?? ?????? ??????????
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
    this->step_dx = this->dx * TimeManager::GetDeltaTime();
    this->step_dy = this->dy * TimeManager::GetDeltaTime();
}