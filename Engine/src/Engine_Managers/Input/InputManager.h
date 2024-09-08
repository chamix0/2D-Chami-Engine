#pragma once
#include <map>
#include <set>
#include <string>
#include <unordered_map>

#include "InputKeys.h"
#include "JoyStickValue.h"

class InputManager
{
private:
    std::unordered_map<int, std::string> abecedaryMap = {
        {vk_0, "0"}, {vk_1, "1"}, {vk_2, "2"}, {vk_3, "3"}, {vk_4, "4"}, {vk_5, "5"},
        {vk_6, "6"}, {vk_7, "7"}, {vk_8, "8"}, {vk_9, "9"}, {vk_A, "A"}, {vk_B, "B"}, {vk_C, "C"}, {vk_D, "D"},
        {vk_E, "E"}, {vk_F, "F"}, {vk_G, "G"}, {vk_H, "H"}, {vk_I, "I"}, {vk_J, "J"}, {vk_K, "K"}, {vk_L, "L"},
        {vk_M, "M"}, {vk_N, "N"}, {vk_O, "O"}, {vk_P, "P"}, {vk_Q, "Q"}, {vk_R, "R"}, {vk_S, "S"}, {vk_T, "T"},
        {vk_U, "U"}, {vk_V, "V"}, {vk_W, "W"}, {vk_X, "X"}, {vk_Y, "Y"}, {vk_Z, "Z"}, {vk_LWin, "LWin"},
        {vk_Comma, ","}, {vk_Period, "."}, {vk_Apostrophe, "Apostrophe"}, {VK_SPACE, " "}
    };
    std::unordered_map<int, std::string> vkMap = {
        {vk_BackSpace, "BackSpace"}, {vk_Tab, "Tab"}, {vk_Return, "Return"},
        {vk_Control, "Control"},
        {vk_Alt, "Alt"}, {vk_Pause, "Pause"}, {vk_CapsLock, "CapsLock"}, {vk_Escape, "Escape"}, {vk_Space, "Space"},
        {vk_PageUp, "PageUp"}, {vk_PageDown, "PageDown"}, {vk_End, "End"}, {vk_Home, "Home"}, {vk_Left, "Left"},
        {vk_Up, "Up"}, {vk_Right, "Right"}, {vk_Down, "Down"}, {vk_PrintScreen, "PrintScreen"}, {vk_Insert, "Insert"},
        {vk_Delete, "Delete"}, {vk_0, "0"}, {vk_1, "1"}, {vk_2, "2"}, {vk_3, "3"}, {vk_4, "4"}, {vk_5, "5"},
        {vk_6, "6"}, {vk_7, "7"}, {vk_8, "8"}, {vk_9, "9"}, {vk_A, "A"}, {vk_B, "B"}, {vk_C, "C"}, {vk_D, "D"},
        {vk_E, "E"}, {vk_F, "F"}, {vk_G, "G"}, {vk_H, "H"}, {vk_I, "I"}, {vk_J, "J"}, {vk_K, "K"}, {vk_L, "L"},
        {vk_M, "M"}, {vk_N, "N"}, {vk_O, "O"}, {vk_P, "P"}, {vk_Q, "Q"}, {vk_R, "R"}, {vk_S, "S"}, {vk_T, "T"},
        {vk_U, "U"}, {vk_V, "V"}, {vk_W, "W"}, {vk_X, "X"}, {vk_Y, "Y"}, {vk_Z, "Z"}, {vk_LWin, "LWin"},
        {vk_RWin, "RWin"}, {vk_Apps, "Apps"}, {vk_NumPad0, "NumPad0"}, {vk_NumPad1, "NumPad1"}, {vk_NumPad2, "NumPad2"},
        {vk_NumPad3, "NumPad3"}, {vk_NumPad4, "NumPad4"}, {vk_NumPad5, "NumPad5"}, {vk_NumPad6, "NumPad6"},
        {vk_NumPad7, "NumPad7"}, {vk_NumPad8, "NumPad8"}, {vk_NumPad9, "NumPad9"}, {vk_Multiply, "Multiply"},
        {vk_Add, "Add"}, {vk_Subtract, "Subtract"}, {vk_Decimal, "Decimal"}, {vk_Divide, "Divide"}, {vk_F1, "F1"},
        {vk_F2, "F2"}, {vk_F3, "F3"}, {vk_F4, "F4"}, {vk_F5, "F5"}, {vk_F6, "F6"}, {vk_F7, "F7"}, {vk_F8, "F8"},
        {vk_F9, "F9"}, {vk_F10, "F10"}, {vk_F11, "F11"}, {vk_F12, "F12"}, {vk_F13, "F13"}, {vk_F14, "F14"},
        {vk_F15, "F15"}, {vk_F16, "F16"}, {vk_NumLock, "NumLock"}, {vk_ScrollLock, "ScrollLock"}, {vk_LShift, "LShift"},
        {vk_RShift, "RShift"}, {vk_LControl, "LControl"}, {vk_RControl, "RControl"}, {vk_LAlt, "LAlt"},
        {vk_RAlt, "RAlt"}, {vk_SemiColon, "SemiColon"}, {vk_Equals, "Equals"}, {vk_Comma, ","},
        {vk_UnderScore, "UnderScore"}, {vk_Period, "."}, {vk_Slash, "Slash"}, {vk_BackSlash, "BackSlash"},
        {vk_RightBrace, "RightBrace"}, {vk_LeftBrace, "LeftBrace"}, {vk_Apostrophe, "Apostrophe"},
        {GAMEPAD_SOUTH, "GAMEPAD_SOUTH"}, {GAMEPAD_EAST, "GAMEPAD_EAST"}, {GAMEPAD_WEST, "GAMEPAD_WEST"},
        {GAMEPAD_NORTH, "GAMEPAD_NORTH"}, {GAMEPAD_DPAD_UP, "GAMEPAD_DPAD_UP"},
        {GAMEPAD_DPAD_DOWN, "GAMEPAD_DPAD_DOWN"},
        {GAMEPAD_DPAD_LEFT, "GAMEPAD_DPAD_LEFT"}, {GAMEPAD_DPAD_RIGHT, "GAMEPAD_DPAD_RIGHT"},
        {GAMEPAD_START, "GAMEPAD_START"},
        {GAMEPAD_SELECT, "GAMEPAD_SELECT"}, {GAMEPAD_LEFT_SHOULDER, "GAMEPAD_LEFT_SHOULDER"},
        {GAMEPAD_RIGHT_SHOULDER, "GAMEPAD_RIGHT_SHOULDER"},
        {GAMEPAD_RIGHT_THUMB, "GAMEPAD_RIGHT_THUMB"},
    };

    const int registeredKeyboardInputs[68] = {
        vk_BackSpace, vk_Tab, vk_Return, vk_Control, vk_Alt, vk_Pause, vk_CapsLock, vk_Escape, vk_Space,
        vk_Left, vk_Up, vk_Right, vk_Down, vk_PrintScreen, vk_Insert,
        vk_Delete, vk_Period,
        vk_0, vk_1, vk_2, vk_3, vk_4, vk_5, vk_6, vk_7, vk_8, vk_9,
        vk_A, vk_B, vk_C, vk_D, vk_E, vk_F, vk_G, vk_H, vk_I, vk_J, vk_K, vk_L, vk_M, vk_N, vk_O, vk_P, vk_Q, vk_R,
        vk_S, vk_T, vk_U, vk_V, vk_W, vk_X, vk_Y, vk_Z,
        vk_LWin, vk_RWin, vk_Apps, vk_LShift,
        vk_F1, vk_F2, vk_F3, vk_F4, vk_F5, vk_F6, vk_F7, vk_F8, vk_F9, vk_F10, vk_Comma
    };
    const int registeredGamepadInputs[13] = {
        GAMEPAD_SOUTH, GAMEPAD_EAST, GAMEPAD_WEST, GAMEPAD_NORTH,
        GAMEPAD_DPAD_UP, GAMEPAD_DPAD_DOWN, GAMEPAD_DPAD_LEFT, GAMEPAD_DPAD_RIGHT,
        GAMEPAD_START, GAMEPAD_SELECT,
        GAMEPAD_LEFT_SHOULDER, GAMEPAD_RIGHT_SHOULDER, GAMEPAD_LEFT_THUMB
    };

    std::map<int, bool> pressed;
    std::set<int> InputsPressed, InputThisFrame;
    std::string currentAbcKey;

    //gamepad axis
    JoyStickValue leftJoystick;
    JoyStickValue rightJoystick;
    float rightTrigger = 0.f;
    float leftTrigger = 0.f;

public:
    InputManager();
    void UpdateInputs();
    std::set<int> GetPressedInputs() const;
    std::set<int> GetThisFrameInputs() const;
    bool CheckPressedInput(int key);
    bool CheckInstantInput(int key);


    JoyStickValue GetLeftJoyStick() const;
    JoyStickValue GetRightJoyStick() const;
    /// \brief get the pressed amount from 0 to 1
    /// \return 
    float GetLeftTrigger() const;
    /// \brief get the pressed amount from 0 to 1
    /// \return 
    float GetRightTrigger() const;

    /// \brief get the string value of an input
    /// \param inputKey 
    /// \return input string
    std::string InputToString(int inputKey);

    Vec2 GetCursorPos();
    std::string GetCurrentAbcKey();

private:
    void ProcessInput(int key, std::set<int>& inputsPressed, std::set<int>& inputsThisFrame);
    void ProcessInputGamepad(int key, std::set<int>& inputsPressed, std::set<int>& inputsThisFrame);
    void ProcessAxis();
    void ProcessLeftJoyStick(XINPUT_STATE& state);
    void ProcessRightJoyStick(XINPUT_STATE& state);
    void ProcessLeftTrigger(XINPUT_STATE& state);
    void ProcessRightTrigger(XINPUT_STATE& state);
};
