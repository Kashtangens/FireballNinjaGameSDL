#ifndef INFO_MODULE_H
#define INFO_MODULE_H

#include <string>

#define playerSpeedConstant 100

//Информация пользователя---------------------------------------
namespace Info
{
// Информация о скинах персонажа
extern int playerSkinNumber;
extern int fireballSkinNumber;
extern std::string playerSkinsPaths[];

// Информация о типе управления
enum InputType {
    KeyboardOnly,
    KeyboardWithMouse,
    GamePad
};

extern InputType inputType;
extern InputType lastInputType;

extern int cameraX;
extern int cameraY;

};
//--------------------------------------------------------------

#endif