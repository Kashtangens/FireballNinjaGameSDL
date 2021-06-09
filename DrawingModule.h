#ifndef DRAWING_MODULE_H
#define DRAWING_MODULE_H

#define DEFAULT_WIDTH 480
#define DEFAULT_HEIGHT 320

#include <iostream>

// Инклудим библиотеки sdl в условии, чтобы они не дублировались
#ifndef SDL_INCLUDES
#define SDL_INCLUDES

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

#include "InfoModule.h"
#include "SoundModule.h"

//Абстрактные классы(интерфейсы)----------------------------------------------------------------
// Класс отображаемого объекта
class Drawable
{
protected:
    void* selfDrawable;
public:
    bool isActive;
    virtual void Draw(SDL_Renderer *renderer) {};
    Drawable* GetSelfDrawable();
};

// Класс подписчика на события
class EventListener
{
protected:
    void* selfEventListener;
public:
    bool isActive;
    virtual void HandleEvent(SDL_Event &event) {};
    EventListener* GetEventSubscriber();
};
//----------------------------------------------------------------------------------------------

//Списки рисуемых и прослушивающих события------------------------------------------------------
struct DrawableListStruct
{
    DrawableListStruct* prev;
    Drawable* drawableObject;
    DrawableListStruct* next;
};

class DrawableListClass
{
public:
    DrawableListClass();
    DrawableListStruct* Add(Drawable *drawableObject);
    void DeleteAll();
    void DrawAll(SDL_Renderer* renderer);
private:
    DrawableListStruct* head;
    void DeleteElement(DrawableListStruct *deletableElement);
};

struct EventListenersListStruct
{
    EventListenersListStruct* prev;
    EventListener* eventListener;
    EventListenersListStruct* next;
};

class EventListenersListClass
{
public:
    EventListenersListClass();
    EventListenersListStruct* Add(EventListener *eventListener);
    void DeleteAll();
    void HandleEventAll(SDL_Event &event);
private:
    EventListenersListStruct* head;
    void DeleteElement(EventListenersListStruct *deletableElement);
};

//----------------------------------------------------------------------------------------------

// Флаги привязки координат 
#define SR_HorizontalAlignment_Left 1
#define SR_HorizontalAlignment_Center 2
#define SR_HorizontalAlignment_Right 3
#define SR_VerticalAlignment_Top 4 
#define SR_VerticalAlignment_Center 8 
#define SR_VerticalAlignment_Bottom 12  

struct FloatRect
{
    float x;
    float y;
    int w;
    int h;
};

class ScalableRect
{
public:
    ScalableRect();

    ScalableRect(float x, float y, int w, int h, void* wnd, uint8_t alignmentFlags);

    ScalableRect(const ScalableRect &rect);

    FloatRect GetStartRect();

    SDL_Rect GetRect();

    SDL_Rect* GetRectPointer();

    void SetXY(float x, float y);

    void TranslateXY(float dx, float dy);

private:
    void *wnd;
    int last_screen_width, last_screen_height;
    // float lastScalerValue;
    SDL_Rect mathRect;
    FloatRect startRect;
    SDL_Rect renderableRect;
    uint8_t alignmentFlags;

    void UpdateRect();
};

//Класс камеры----------------------------------------------------------------------------------

class Camera
{
public:
    ScalableRect* rect;

    Camera();

    Camera(ScalableRect &rect);

    void SetFollowableObject(ScalableRect *followableObject, ScalableRect *mapRect);

    void Update();

private:
    ScalableRect* followableObject;
    ScalableRect* mapRect;
};

//----------------------------------------------------------------------------------------------

class Window
{
public:
    SDL_Renderer* renderer;
    Camera camera;

    enum WindowEvent{
        None, Close
    };

    Window();

    ~Window();

    bool Init(std::string title="title", int screen_width = 640, int screen_height = 480);

    int GetScreenWidth();

    int GetScreenHeight();

    void SetScreenWidht();

    void SetScreenHeight();

    float GetScaler();

    void RenderAll(DrawableListClass &drawableObjects);

    WindowEvent HandleAllEvents(EventListenersListClass &eventListeners);

private:
    int screen_width;
    int screen_height;
    float scaler;
    SDL_Window* window;
    
    void SetScaler(int width, int height);
};

//Классы элементов интерфейса-------------------------------------------------------------------
// Класс кнопки
class UiButton: public Drawable, public EventListener
{
    public:
    // rect содержит позицию и размеры кнопки
    ScalableRect rect;

    UiButton();

    UiButton(ScalableRect &rect, SDL_Texture *defaultTexture, SDL_Texture *mouseOverTexture, SDL_Texture *clickedTexture, void (*OnClickFunc) (UiButton *sender), void (*MouseOverFunc) (UiButton *sender), DrawableListClass *drawableList, EventListenersListClass *eventListenersList);

    ~UiButton();

    void HandleEvent(SDL_Event &event);

    void Draw(SDL_Renderer *renderer);

    void SetOnClickFunction(void (*OnClickFunc) (UiButton *sender));

    void SetMouseOverFunction(void (*MouseOverFunc) (UiButton *sender));
    
    void SetTextures(SDL_Texture *defaultTexture, SDL_Texture *mouseOverTexture, SDL_Texture *clickedTexture);

    private:
    enum ButtonStates {
        DefaultState, MouseOverState, ClickedState, StatesCount
    } state;
    SDL_Texture* textures[StatesCount];
    void (*OnClick) (UiButton *sender);
    void (*MouseOver) (UiButton *sender);
};

//----------------------------------------------------------------------------------------------

SDL_Texture* loadTexture(std::string path, SDL_Renderer *renderer);

int myFloor(double number);

#endif