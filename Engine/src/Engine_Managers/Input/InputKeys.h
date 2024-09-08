#pragma once
#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")

#define GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define GAMEPAD_TRIGGER_THRESHOLD    5

const int vk_BackSpace = 8;
const int vk_Tab = 9;
const int vk_Return = 13;
// const int vk_Shift = 16;
const int vk_Control = 17;
const int vk_Alt = 18;
const int vk_Pause = 19;
const int vk_CapsLock = 20;
const int vk_Escape = 27;
const int vk_Space = 32;
const int vk_PageUp = 33;
const int vk_PageDown = 34;
const int vk_End = 35;
const int vk_Home = 36;
const int vk_Left = 37;
const int vk_Up = 38;
const int vk_Right = 39;
const int vk_Down = 40;
const int vk_PrintScreen = 44;
const int vk_Insert = 45;
const int vk_Delete = 46;

/* NOTE: vk_0..vk_9 vk_A.. vk_Z match regular ASCII codes for digits and A-Z letters */

const int vk_0 = 48;
const int vk_1 = 49;
const int vk_2 = 50;
const int vk_3 = 51;
const int vk_4 = 52;
const int vk_5 = 53;
const int vk_6 = 54;
const int vk_7 = 55;
const int vk_8 = 56;
const int vk_9 = 57;
const int vk_A = 65;
const int vk_B = 66;
const int vk_C = 67;
const int vk_D = 68;
const int vk_E = 69;
const int vk_F = 70;
const int vk_G = 71;
const int vk_H = 72;
const int vk_I = 73;
const int vk_J = 74;
const int vk_K = 75;
const int vk_L = 76;
const int vk_M = 77;
const int vk_N = 78;
const int vk_O = 79;
const int vk_P = 80;
const int vk_Q = 81;
const int vk_R = 82;
const int vk_S = 83;
const int vk_T = 84;
const int vk_U = 85;
const int vk_V = 86;
const int vk_W = 87;
const int vk_X = 88;
const int vk_Y = 89;
const int vk_Z = 90;
const int vk_LWin = 91;
const int vk_RWin = 92;
const int vk_Apps = 93;
/* numerical key pad */
const int vk_NumPad0 = 96;
const int vk_NumPad1 = 97;
const int vk_NumPad2 = 98;
const int vk_NumPad3 = 99;
const int vk_NumPad4 = 100;
const int vk_NumPad5 = 101;
const int vk_NumPad6 = 102;
const int vk_NumPad7 = 103;
const int vk_NumPad8 = 104;
const int vk_NumPad9 = 105;
const int vk_Multiply = 106;
const int vk_Add = 107;
const int vk_Subtract = 109;
const int vk_Decimal = 110;
const int vk_Divide = 111;
/* function keys */
const int vk_F1 = 112;
const int vk_F2 = 113;
const int vk_F3 = 114;
const int vk_F4 = 115;
const int vk_F5 = 116;
const int vk_F6 = 117;
const int vk_F7 = 118;
const int vk_F8 = 119;
const int vk_F9 = 120;
const int vk_F10 = 121;
const int vk_F11 = 122;
const int vk_F12 = 123;
const int vk_F13 = 124;
const int vk_F14 = 125;
const int vk_F15 = 126;
const int vk_F16 = 127;

const int vk_NumLock = 144;
const int vk_ScrollLock = 145;
const int vk_LShift = 160;
const int vk_RShift = 161;
const int vk_LControl = 162;
const int vk_RControl = 163;
const int vk_LAlt = 164;
const int vk_RAlt = 165;
const int vk_SemiColon = 186;
const int vk_Equals = 187;
const int vk_Comma = 188;
const int vk_UnderScore = 189;
const int vk_Period = 190;
const int vk_Slash = 191;
const int vk_BackSlash = 220;
const int vk_RightBrace = 221;
const int vk_LeftBrace = 219;
const int vk_Apostrophe = 222;

/*gamepad*/
//buttons
const int GAMEPAD_SOUTH = XINPUT_GAMEPAD_A;
const int GAMEPAD_EAST = XINPUT_GAMEPAD_B;
const int GAMEPAD_WEST = XINPUT_GAMEPAD_X;
const int GAMEPAD_NORTH = XINPUT_GAMEPAD_Y;
//D-PAD
const int GAMEPAD_DPAD_UP = XINPUT_GAMEPAD_DPAD_UP;
const int GAMEPAD_DPAD_DOWN = XINPUT_GAMEPAD_DPAD_DOWN;
const int GAMEPAD_DPAD_LEFT = XINPUT_GAMEPAD_DPAD_LEFT;
const int GAMEPAD_DPAD_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT;
//special buttons
const int GAMEPAD_START = XINPUT_GAMEPAD_START;
const int GAMEPAD_SELECT = XINPUT_GAMEPAD_BACK;
//shoulders
const int GAMEPAD_LEFT_SHOULDER = XINPUT_GAMEPAD_LEFT_SHOULDER;
const int GAMEPAD_RIGHT_SHOULDER = XINPUT_GAMEPAD_RIGHT_SHOULDER;

//Joysticks
//left
const int GAMEPAD_LEFT_THUMB = XINPUT_GAMEPAD_LEFT_THUMB;

//right
const int GAMEPAD_RIGHT_THUMB = XINPUT_GAMEPAD_RIGHT_THUMB;
