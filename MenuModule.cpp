#include "MenuModule.h"
#include "SingleplayerModule.h"

// Реализация класса MenuManager
MenuState MenuManager::state = MenuState::MainMenu;
MenuState MenuManager::lastState = MenuState::MainMenu;
std::vector<UiButton*> MenuManager::buttons = std::vector<UiButton*>();
bool MenuManager::isExit = false;

void MenuManager::initMenusUIElements(DrawableListClass *drawableList, EventListenersListClass *eventListenersList, Window *wnd, MapManager* mapManager)
{
    switch (MenuManager::state)
    {
        case MenuState::MainMenu:
        {
            // Создание кнопок меню
            // Кнопка "Играть"
            ScalableRect playButtonRect = ScalableRect(0, 10, 128, 32, wnd, SR_HorizontalAlignment_Center | SR_VerticalAlignment_Top);
            UiButton* playButton = new UiButton(playButtonRect, loadTexture("textures/Buttons/PlayButton/PlayButtonDefault.png", wnd->renderer), loadTexture("textures/Buttons/PlayButton/PlayButtonMouseOver.png", wnd->renderer), loadTexture("textures/Buttons/PlayButton/PlayButtonOnClick.png", wnd->renderer), playButtonOnClick, NULL, drawableList, eventListenersList);
            buttons.push_back(playButton);
            // Кнопка "Редактор карт"
            ScalableRect mapEditorButtonRect = ScalableRect(0, 52, 128, 32, wnd, SR_HorizontalAlignment_Center | SR_VerticalAlignment_Top);
            UiButton* mapEditorButton = new UiButton(mapEditorButtonRect, loadTexture("textures/Buttons/MapEditorButton/MapEditorButtonDefault.png", wnd->renderer), loadTexture("textures/Buttons/MapEditorButton/MapEditorButtonMouseOver.png", wnd->renderer), loadTexture("textures/Buttons/MapEditorButton/MapEditorButtonOnClick.png", wnd->renderer), mapEditorButtonOnClick, NULL, drawableList, eventListenersList);
            buttons.push_back(mapEditorButton);
            // Кнопка "Редактор персонажа"
            ScalableRect skinShopButtonRect = ScalableRect(0, 94, 128, 32, wnd, SR_HorizontalAlignment_Center | SR_VerticalAlignment_Top);
            UiButton* skinShopButton = new UiButton(skinShopButtonRect, loadTexture("textures/Buttons/SkinShopButton/SkinShopButtonDefault.png", wnd->renderer), loadTexture("textures/Buttons/SkinShopButton/SkinShopButtonMouseOver.png", wnd->renderer), loadTexture("textures/Buttons/SkinShopButton/SkinShopButtonOnClick.png", wnd->renderer), skinShopButtonOnClick, NULL, drawableList, eventListenersList);
            buttons.push_back(skinShopButton);
            // Кнопка "Настройки"
            ScalableRect settingsButtonRect = ScalableRect(0, 136, 128, 32, wnd, SR_HorizontalAlignment_Center | SR_VerticalAlignment_Top);
            UiButton* settingsButton = new UiButton(settingsButtonRect, loadTexture("textures/Buttons/SettingsButton/SettingsButtonDefault.png", wnd->renderer), loadTexture("textures/Buttons/SettingsButton/SettingsButtonMouseOver.png", wnd->renderer), loadTexture("textures/Buttons/SettingsButton/SettingsButtonOnClick.png", wnd->renderer), settingsButtonOnClick, NULL, drawableList, eventListenersList);
            buttons.push_back(settingsButton);
            // Кнопка "Выход"
            ScalableRect exitButtonRect = ScalableRect(0, 178, 128, 32, wnd, SR_HorizontalAlignment_Center | SR_VerticalAlignment_Top);
            UiButton* exitButton = new UiButton(exitButtonRect, loadTexture("textures/Buttons/ExitButton/ExitButtonDefault.png", wnd->renderer), loadTexture("textures/Buttons/ExitButton/ExitButtonMouseOver.png", wnd->renderer), loadTexture("textures/Buttons/ExitButton/ExitButtonOnClick.png", wnd->renderer), exitButtonOnClick, NULL, drawableList, eventListenersList);
            buttons.push_back(exitButton);
            break;
        }
        case Settings:
        {
            // Кнопка выбора режима управления
            ScalableRect inputModeButtonRect = ScalableRect(0, 10, 128, 32, wnd, SR_HorizontalAlignment_Center | SR_VerticalAlignment_Top);
            if (Info::inputType == Info::InputType::GamePad)
            {
                UiButton* inputModeButton = new UiButton(inputModeButtonRect, loadTexture("textures/Buttons/InputModeButton/GamepadButtonDefault.png", wnd->renderer), loadTexture("textures/Buttons/InputModeButton/GamepadButtonMouseOver.png", wnd->renderer), loadTexture("textures/Buttons/InputModeButton/GamepadButtonOnClick.png", wnd->renderer), inputModeButtonOnClick, NULL, drawableList, eventListenersList);
                buttons.push_back(inputModeButton);
            }
            else if (Info::inputType == Info::InputType::KeyboardOnly)
            {
                UiButton* inputModeButton = new UiButton(inputModeButtonRect, loadTexture("textures/Buttons/InputModeButton/KeyboardButtonDefault.png", wnd->renderer), loadTexture("textures/Buttons/InputModeButton/KeyboardButtonMouseOver.png", wnd->renderer), loadTexture("textures/Buttons/InputModeButton/KeyboardButtonOnClick.png", wnd->renderer), inputModeButtonOnClick, NULL, drawableList, eventListenersList);
                buttons.push_back(inputModeButton);
            }
            else if (Info::inputType == Info::InputType::KeyboardWithMouse)
            {
                UiButton* inputModeButton = new UiButton(inputModeButtonRect, loadTexture("textures/Buttons/InputModeButton/KeyboardWithMouseButtonDefault.png", wnd->renderer), loadTexture("textures/Buttons/InputModeButton/KeyboardWithMouseButtonMouseOver.png", wnd->renderer), loadTexture("textures/Buttons/InputModeButton/KeyboardWithMouseButtonOnClick.png", wnd->renderer), inputModeButtonOnClick, NULL, drawableList, eventListenersList);
                buttons.push_back(inputModeButton);
            }
            // Кнопка "назад"
            ScalableRect backButtonRect = ScalableRect(0, 52, 128, 32, wnd, SR_HorizontalAlignment_Center | SR_VerticalAlignment_Top);
            UiButton* backButton = new UiButton(backButtonRect, loadTexture("textures/Buttons/BackButton/BackButtonDefault.png", wnd->renderer), loadTexture("textures/Buttons/BackButton/BackButtonMouseOver.png", wnd->renderer), loadTexture("textures/Buttons/BackButton/BackButtonOnClick.png", wnd->renderer), backButtonOnClick, NULL, drawableList, eventListenersList);
            buttons.push_back(backButton);
            break;
        }
        // case SkinShop:

        //     break;
        // case MapEditor:

        //     break;
        // case InGameMenu:

        //     break;
        // case MultiOrSinglePlayerSelector:

        //     break;
        // case MapSelector:

        //     break;
        case MenuState::SinglePlayerState:
        {
            // Кнопка "назад"
            ScalableRect backButtonRect = ScalableRect(10, 10, 64, 16, wnd, SR_HorizontalAlignment_Right | SR_VerticalAlignment_Bottom);
            UiButton* backButton = new UiButton(backButtonRect, loadTexture("textures/Buttons/BackButton/BackButtonDefault.png", wnd->renderer), loadTexture("textures/Buttons/BackButton/BackButtonMouseOver.png", wnd->renderer), loadTexture("textures/Buttons/BackButton/BackButtonOnClick.png", wnd->renderer), exitSinglePlayerOnClick, NULL, drawableList, eventListenersList);
            buttons.push_back(backButton);
            // Отрисовка здоровья персонажа
            
            // Старт одиночной игры
            SinglePlayer::StartLevel(drawableList, eventListenersList, wnd, mapManager);
            break;
        }
        // case SessionCreation:

        //     break;
        // case CheckForSession:

        //     break;
        // case Login:

        //     break;
        // case PlayerSelector:

        //     break;
        // case SessionLobby:

        //     break;
        // case MultiPlayer:

        //     break;
    }
}

void MenuManager::setMenuState(MenuState menuState)
{
    MenuManager::state = menuState;
}

void MenuManager::closeMenuUIElements()
{
    for (auto button = buttons.begin(); button != buttons.end(); button++)
    {
        delete(*button);
    }
    buttons.clear();
}

void MenuManager::menuIteration(DrawableListClass *drawableList, EventListenersListClass *eventListenersList, Window *wnd, MapManager *mapManager)
{
    if (MenuManager::lastState != MenuManager::state)
    {
        MenuManager::lastState = MenuManager::state;
        MenuManager::initMenusUIElements(drawableList, eventListenersList, wnd, mapManager);
    }
    else
    {
        if (MenuManager::state == MenuState::SinglePlayerState)
            SinglePlayer::PlayIteration(*mapManager);
    }
    if (Info::lastInputType != Info::inputType)
    {
        switch (Info::inputType)
        {
            case Info::InputType::KeyboardOnly:
                buttons.at(buttons.size()-2)->SetTextures(loadTexture("textures/Buttons/InputModeButton/KeyboardButtonDefault.png", wnd->renderer), loadTexture("textures/Buttons/InputModeButton/KeyboardButtonMouseOver.png", wnd->renderer), loadTexture("textures/Buttons/InputModeButton/KeyboardButtonOnClick.png", wnd->renderer));
                break;
            case Info::InputType::KeyboardWithMouse:
                buttons.at(buttons.size()-2)->SetTextures(loadTexture("textures/Buttons/InputModeButton/KeyboardWithMouseButtonDefault.png", wnd->renderer), loadTexture("textures/Buttons/InputModeButton/KeyboardWithMouseButtonMouseOver.png", wnd->renderer), loadTexture("textures/Buttons/InputModeButton/KeyboardWithMouseButtonOnClick.png", wnd->renderer));
                break;
            case Info::InputType::GamePad:
                buttons.at(buttons.size()-2)->SetTextures(loadTexture("textures/Buttons/InputModeButton/GamepadButtonDefault.png", wnd->renderer), loadTexture("textures/Buttons/InputModeButton/GamepadButtonMouseOver.png", wnd->renderer), loadTexture("textures/Buttons/InputModeButton/GamepadButtonOnClick.png", wnd->renderer));
                break;
        }
        Info::lastInputType = Info::inputType;
    }
}

// Реализация событий кнопок главного меню
void playButtonOnClick(UiButton *sender)
{
    MenuManager::setMenuState(MenuState::SinglePlayerState);
    MenuManager::closeMenuUIElements();
}

void mapEditorButtonOnClick(UiButton *sender)
{

}

void skinShopButtonOnClick(UiButton *sender)
{

}

void settingsButtonOnClick(UiButton *sender)
{
    MenuManager::setMenuState(MenuState::Settings);
    MenuManager::closeMenuUIElements();
}

void exitButtonOnClick(UiButton *sender)
{
    MenuManager::isExit = true;
    MenuManager::closeMenuUIElements();
}

void backButtonOnClick(UiButton *sender)
{
    MenuManager::setMenuState(MenuState::MainMenu);
    MenuManager::closeMenuUIElements();
}

void inputModeButtonOnClick(UiButton *sender)
{
    switch (Info::inputType)
    {
        case Info::InputType::GamePad:
            Info::inputType = Info::InputType::KeyboardOnly;
            break;
        case Info::InputType::KeyboardOnly:
            Info::inputType = Info::InputType::KeyboardWithMouse;
            break;
        case Info::InputType::KeyboardWithMouse:
            Info::inputType = Info::InputType::GamePad;
            break;
    }
}

void exitSinglePlayerOnClick(UiButton *sender)
{
    SinglePlayer::ExitLevel();
    MenuManager::setMenuState(MenuState::MainMenu);
    MenuManager::closeMenuUIElements();
}