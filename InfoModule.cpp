#include "InfoModule.h"

//Информация пользователя---------------------------------------
namespace Info
{
// Информация о скинах персонажа
int playerSkinNumber = 0;
int fireballSkinNumber = 0;
std::string playerSkinsPaths[] = 
{
    "textures/Entities/PlayerSprite.png"
};

// Информация о типе управления
InputType inputType = KeyboardOnly;
InputType lastInputType = KeyboardOnly;

int cameraX = 0;
int cameraY = 0;

};
//--------------------------------------------------------------

