#include "DrawingModule.h"

Drawable* Drawable::GetSelfDrawable()
{
    return ((DrawableListStruct*)(this->selfDrawable))->drawableObject;
}

EventListener* EventListener::GetEventSubscriber()
{
    return ((EventListenersListStruct*)(this->selfEventListener))->eventListener;
}

//Списки для рисуемых элементов и для подписчиков на события-----------------------------------------------------

// DrawableListClass

DrawableListClass::DrawableListClass()
{
    this->head = NULL;
}

DrawableListStruct* DrawableListClass::Add(Drawable *drawableObject)
{
    DrawableListStruct* newElement = new DrawableListStruct();
    newElement->drawableObject = drawableObject;
    newElement->next = this->head;
    newElement->prev = NULL;
    if (this->head != NULL)
    {
        this->head->prev = newElement;
    }
    this->head = newElement;
    return this->head;
}

void DrawableListClass::DeleteAll()
{

}

void DrawableListClass::DrawAll(SDL_Renderer* renderer)
{
    // printf("Start drawing\n");
    DrawableListStruct* current = this->head;
    while (current != NULL)
    {
        // printf("%u\n", current);
        if (current->drawableObject != NULL)
        {
            current->drawableObject->Draw(renderer);
        }
        current = current->next;
    }
    // printf("End drawing\n");
}

void DrawableListClass::DeleteElement(DrawableListStruct *deletableElement)
{

}

// EventListenersListClass

EventListenersListClass::EventListenersListClass()
{
    this->head = NULL;
}

EventListenersListStruct* EventListenersListClass::Add(EventListener *eventListener)
{
    EventListenersListStruct* newElement = new EventListenersListStruct();
    newElement->eventListener = eventListener;
    newElement->next = this->head;
    newElement->prev = NULL;
    if (this->head != NULL)
    {
        this->head->prev = newElement;
    }
    this->head = newElement;
    return this->head;
}

void EventListenersListClass::DeleteAll()
{

}

void EventListenersListClass::HandleEventAll(SDL_Event &event)
{
    EventListenersListStruct* current = this->head;
    while(current != NULL)
    {
        if (current->eventListener != NULL)
        {
            current->eventListener->HandleEvent(event);
        }
        current = current->next;
    }
}

void EventListenersListClass::DeleteElement(EventListenersListStruct *deletableElement)
{

}

//---------------------------------------------------------------------------------------------------------------

//ScalableRect---------------------------------------------------------------------------------------------------

ScalableRect::ScalableRect()
{
    wnd = NULL;
    // lastScalerValue = 0;
    last_screen_height = 0;
    last_screen_width = 0;
    alignmentFlags = SR_HorizontalAlignment_Left | SR_VerticalAlignment_Top;
    startRect = {0, 0, 0, 0};  
    mathRect = {0, 0, 0, 0}; 
    renderableRect = {0, 0, 0, 0};
} 

ScalableRect::ScalableRect(float x, float y, int w, int h, void* wnd, uint8_t alignmentFlags)
{
    this->alignmentFlags = alignmentFlags;
    if (wnd != NULL)
    {
        this->wnd = wnd;
        // this->lastScalerValue = ((Window*)wnd)->GetScaler();
        this->last_screen_width = ((Window*)wnd)->GetScreenWidth();
        this->last_screen_height = ((Window*)wnd)->GetScreenHeight();
        this->startRect = {x, y, w, h};
        this->UpdateRect();
    }
    else
    {
        this->wnd = NULL;
        last_screen_height = 0;
        last_screen_width = 0;
        this->startRect = {x, y, w, h};
        this->UpdateRect();
    }
}

ScalableRect::ScalableRect(const ScalableRect &rect)
{
        this->wnd = rect.wnd;
        // this->lastScalerValue = rect.lastScalerValue;
        this->last_screen_width = rect.last_screen_width;
        this->last_screen_height = rect.last_screen_height;
        this->startRect = {rect.startRect.x, rect.startRect.y, rect.startRect.w, rect.startRect.h};
        this->mathRect = {rect.mathRect.x, rect.mathRect.y, rect.mathRect.w, rect.mathRect.h};
        this->renderableRect = {rect.renderableRect.x, rect.renderableRect.y, rect.renderableRect.w, rect.renderableRect.h};
        this->alignmentFlags = rect.alignmentFlags;
}

SDL_Rect ScalableRect::GetRect()
{
    if (wnd != NULL){
        if (this->last_screen_width != ((Window*)wnd)->GetScreenWidth() || this->last_screen_height != ((Window*)wnd)->GetScreenHeight())
        {
            this->UpdateRect();
        }
    }
    return this->mathRect;
}

FloatRect ScalableRect::GetStartRect()
{
    return this->startRect;
}

SDL_Rect* ScalableRect::GetRectPointer()
{
    if (wnd != NULL){
        if (this->last_screen_width != ((Window*)wnd)->GetScreenWidth() || this->last_screen_height != ((Window*)wnd)->GetScreenHeight())
        {
            this->UpdateRect();
        }
        if (((this->alignmentFlags & 0b00000011) == SR_HorizontalAlignment_Left) && ((this->alignmentFlags & 0b00001100) == SR_VerticalAlignment_Top))
            this->renderableRect = {this->mathRect.x - int(((Window*)wnd)->camera.rect->startRect.x), this->mathRect.y - int(((Window*)wnd)->camera.rect->startRect.y), this->mathRect.w, this->mathRect.h};
    }
    return &this->renderableRect;
}

void ScalableRect::SetXY(float x, float y)
{
    startRect.x = x;
    startRect.y = y;
    UpdateRect();
}

void ScalableRect::TranslateXY(float dx, float dy)
{
    startRect.x += dx;
    startRect.y += dy;
    UpdateRect();
}

void ScalableRect::UpdateRect()
{
    int scaler = myFloor(((Window*)wnd)->GetScaler());
    int mathX, mathY, mathW, mathH;
    int renderX, renderY;
    // По горизонтали
    switch (this->alignmentFlags & 0b00000011)
    {
        case (SR_HorizontalAlignment_Center):
            mathX = (((Window*)wnd)->GetScreenWidth() / 2) + ((int)(startRect.x) - startRect.w / 2) * scaler;
            mathW = startRect.w * scaler;
            renderX = (((Window*)wnd)->GetScreenWidth() / 2) + ((int)(startRect.x) - startRect.w / 2) * scaler;
            break;
        case (SR_HorizontalAlignment_Right):
            mathX = ((Window*)wnd)->GetScreenWidth() - (startRect.w + (int)(startRect.x)) * scaler;
            mathW = startRect.w * scaler;
            renderX = ((Window*)wnd)->GetScreenWidth() - (startRect.w + (int)(startRect.x)) * scaler;
            break;   
        default: // SR_HorizontalAligment_Left:
            mathX = int(startRect.x) * scaler;
            mathW = startRect.w * scaler;
            renderX = int(startRect.x) * scaler;
            break;     
    }
    // По вертикали
    switch (this->alignmentFlags & 0b00001100)
    {
        case (SR_VerticalAlignment_Center):
            mathY = (((Window*)wnd)->GetScreenHeight() / 2) + ((int)(startRect.y) - startRect.h / 2) * scaler;
            mathH = startRect.h * scaler;
            renderY = (((Window*)wnd)->GetScreenHeight() / 2) + ((int)(startRect.y) - startRect.h / 2) * scaler;
            break;
        case (SR_VerticalAlignment_Bottom):
            mathY = ((Window*)wnd)->GetScreenHeight() - (startRect.h + (int)(startRect.y)) * scaler;
            mathH = startRect.h * scaler;
            renderY = ((Window*)wnd)->GetScreenHeight() - (startRect.h + (int)(startRect.y)) * scaler;
            break;   
        default: // SR_VerticalAligment_Top:
            mathY = int(startRect.y) * scaler;
            mathH = startRect.h * scaler;
            renderY = int(startRect.y) * scaler;
            break;     
    }
    this->mathRect = {mathX, mathY, mathW, mathH};
    this->renderableRect = {mathX, mathY, mathW, mathH};
    // this->lastScalerValue = ((Window*)wnd)->GetScaler();
    this->last_screen_width = ((Window*)wnd)->GetScreenWidth();
    this->last_screen_height = ((Window*)wnd)->GetScreenHeight();
}

//---------------------------------------------------------------------------------------------------------------

//CAMERA---------------------------------------------------------------------------------------------------------
Camera::Camera()
{
    this->rect = new ScalableRect();
    this->followableObject = NULL;
    this->mapRect = NULL;
}

Camera::Camera(ScalableRect &rect)
{
    this->rect = new ScalableRect(rect);
    this->followableObject = NULL;
    this->mapRect = NULL;
}

void Camera::SetFollowableObject(ScalableRect *followableObject, ScalableRect *mapRect)
{
    this->followableObject = followableObject;
    this->mapRect = mapRect;
}

void Camera::Update()
{
    // Если не за кем следовать
    if (this->followableObject == NULL)
    {
        this->rect->SetXY(0, 0);
    }
    // Если есть за кем следовать, то просчитываем логику
    else
    {
        float new_x = this->followableObject->GetRect().x + this->followableObject->GetRect().w / 2 - this->rect->GetStartRect().w / 2;
        float new_y = this->followableObject->GetRect().y + this->followableObject->GetRect().h / 2 - this->rect->GetStartRect().h / 2;
        // printf("Map height: %d; Map width: %d\n", this->mapRect->GetRect().h, this->mapRect->GetRect().w);
        // x
        if (new_x < 0)
        {
            new_x = 0;
        }
        else if ((new_x + this->rect->GetStartRect().w > this->mapRect->GetRect().w) && (this->mapRect->GetRect().w >= this->rect->GetStartRect().w))
        {
            new_x = this->mapRect->GetRect().w - this->rect->GetStartRect().w;
        }
        // y
        if (new_y < 0)
        {
            new_y = 0;
        }
        else if ((new_y + this->rect->GetStartRect().h > this->mapRect->GetRect().h) && (this->mapRect->GetRect().h >= this->rect->GetStartRect().h))
        {
            new_y = this->mapRect->GetRect().h - this->rect->GetStartRect().h;
        }
        this->rect->SetXY(new_x, new_y);
        // printf("Camera position: %f, %f\n", new_x, new_y);
        // printf("Camera rect: %f, %f, %d, %d\n", this->rect->GetStartRect().x, this->rect->GetStartRect().y, this->rect->GetStartRect().w, this->rect->GetStartRect().h);
    }
    Info::cameraX = this->rect->GetStartRect().x;
    Info::cameraY = this->rect->GetStartRect().y;
}

//---------------------------------------------------------------------------------------------------------------

//WINDOW---------------------------------------------------------------------------------------------------------
Window::Window()
{
    this->window = NULL;
    this->renderer = NULL;
    scaler = 0;
    this->camera = Camera();
    // printf("%d %d\n", width, height);
}

bool Window::Init(std::string title, int screen_width, int screen_height)
{
    // window
    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (this->window == NULL)
    {
        return false;
    }
    this->screen_width = screen_width;
    this->screen_height = screen_height;
    // renderer
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (this->renderer == NULL)
    {
        return false;
    }
    SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderSetIntegerScale(this->renderer, SDL_TRUE);
    SetScaler(screen_width, screen_height);
    SDL_DisplayMode DM;
    SDL_GetDesktopDisplayMode(0, &DM);
    return true;
}

void Window::RenderAll(DrawableListClass &drawableObjects)
{
    SDL_RenderClear(this->renderer);
    // SDL_SetRenderTarget(this->renderer, this->buffer);
    SDL_RenderClear(this->renderer);
    this->camera.Update();
    // printf("Camera position: %f, %f\n", this->camera.rect->GetRectPointer()->x, this->camera.rect->GetRectPointer()->y);
    drawableObjects.DrawAll(this->renderer);
    // SDL_SetRenderTarget(this->renderer, NULL);
    // SDL_Rect cameraRect = {int(-this->camera.rect->GetStartRect().x), int(-this->camera.rect->GetStartRect().y), this->display_width, this->display_height};
    // SDL_RenderCopy(this->renderer, this->buffer, NULL, &cameraRect);
    SDL_RenderPresent(this->renderer);
}

Window::WindowEvent Window::HandleAllEvents(EventListenersListClass &eventListeners)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            return WindowEvent::Close;
        }
        else if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                SetScaler(event.window.data1, event.window.data2);
            }
        }
        else
        {
            eventListeners.HandleEventAll(event);
        }
    }
    return WindowEvent::None;
}

float Window::GetScaler()
{
    return this->scaler;
}

void Window::SetScaler(int width, int height)
{
    // По ширине
    if (width < height)
    {
        this->scaler = float(width)/DEFAULT_WIDTH;
    }
    // По высоте
    else
    {
        this->scaler = float(height)/DEFAULT_HEIGHT;
    }
    // printf("width :%d, height: %d, scaler: %f\n", width, height, this->scaler);
    // SDL_RenderSetScale(this->renderer, int(myFloor(scaler)), int(myFloor(scaler)));
    SDL_GetWindowSize(this->window, &this->screen_width, &this->screen_height);
    if (this->camera.rect != NULL)
        delete this->camera.rect;
    this->camera.rect = new ScalableRect(0, 0, this->screen_width, this->screen_height, this, SR_HorizontalAlignment_Left | SR_VerticalAlignment_Top);
    // SDL_RenderSetIntegerScale(this->renderer, true);
}

int Window::GetScreenHeight()
{
    return this->screen_height;
}

int Window::GetScreenWidth()
{
    return this->screen_width;
}

Window::~Window()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    this->window = NULL;
    this->renderer = NULL;
}

//---------------------------------------------------------------------------------------------------------------

//UI BUTTON------------------------------------------------------------------------------------------------------

UiButton::UiButton()
{
    this->state = DefaultState;
    this->rect = ScalableRect();
    for (int i = 0; i < StatesCount; i++)
    {
        this->textures[i] = NULL;
    }
    this->OnClick = NULL;
    this->MouseOver = NULL;
    this->selfDrawable = NULL;
    this->selfEventListener = NULL;
}

UiButton::UiButton(ScalableRect &rect, SDL_Texture *defaultTexture, SDL_Texture *mouseOverTexture, SDL_Texture *clickedTexture, void (*OnClickFunc) (UiButton *sender), void (*MouseOverFunc) (UiButton *sender), DrawableListClass *drawableList, EventListenersListClass *eventListenersList)
{
    this->rect = ScalableRect(rect);
    this->textures[DefaultState] = defaultTexture;
    this->textures[MouseOverState] = mouseOverTexture;
    this->textures[ClickedState] = clickedTexture;
    this->state = DefaultState;
    this->OnClick = OnClickFunc;
    this->MouseOver = MouseOverFunc;
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

UiButton::~UiButton()
{
    for (int i = 0; i < StatesCount; i++)
    {
        SDL_DestroyTexture(this->textures[i]);
        this->textures[i] = NULL;
    }
    if (this->selfDrawable != NULL)
        ((DrawableListStruct*)(this->selfDrawable))->drawableObject = NULL;
    if (this->selfEventListener != NULL)
        ((EventListenersListStruct*)(this->selfEventListener))->eventListener = NULL;
}

void UiButton::SetTextures(SDL_Texture *defaultTexture, SDL_Texture *mouseOverTexture, SDL_Texture *clickedTexture)
{
    this->textures[DefaultState] = defaultTexture;
    this->textures[MouseOverState] = mouseOverTexture;
    this->textures[ClickedState] = clickedTexture; 
}

void UiButton::HandleEvent(SDL_Event &event)
{
    
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        // Проверка на наличие курсора мыши на кнопке
        bool isInside = true;
        if (x < this->rect.GetRect().x)
        {
            isInside = false;
        }
        else if (x > this->rect.GetRect().x + this->rect.GetRect().w)
        {
            isInside = false;
        }
        else if (y < this->rect.GetRect().y)
        {
            isInside = false;
        }
        else if (y > this->rect.GetRect().y + this->rect.GetRect().h)
        {
            isInside = false;
        }
        // Проверка состояния
        if (isInside)
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                this->state = ClickedState;
                if (this->OnClick != NULL)
                {
                    this->OnClick(this);
                }
            }
            else
            {
                this->state = MouseOverState;
                if (this->MouseOver != NULL)
                {
                    this->MouseOver(this);
                }
            }
        }
        else
        {
            this->state = DefaultState;
        }
    }
}

void UiButton::Draw(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, this->textures[this->state], NULL, this->rect.GetRectPointer());
}

//---------------------------------------------------------------------------------------------------------------

SDL_Texture* loadTexture(std::string path, SDL_Renderer *renderer)
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

int myFloor(double number)
{
    if (number != number)
    {
        return 0;
    }
    else
    {
        int result = floor(number);
        if (result < 1)
        {
            return 1;
        }
        else
        {
            return result;
        }
    }
}