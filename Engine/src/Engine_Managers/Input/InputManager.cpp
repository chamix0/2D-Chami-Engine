#include "InputManager.h"

#include "glfw3.h"


InputManager::InputManager()
{
    //init all the inputs as true so it doesnt detect unwanted pressed inputs when changing scenes
    for (int key : registeredKeyboardInputs)
    {
        pressed[key] = true;
    }
    for (int key : registeredGamepadInputs)
    {
        pressed[key] = true;
    }
}

void InputManager::UpdateInputs()
{
    //clean current inputs
    currentAbcKey = "";
    InputsPressed.clear();
    InputThisFrame.clear();
    //process axis
    ProcessAxis();

    //update keyboard inputs
    for (int key : registeredKeyboardInputs)
    {
        ProcessInput(key, InputsPressed, InputThisFrame);
    }

    //update gamepad inputs
    for (int key : registeredGamepadInputs)
    {
        ProcessInputGamepad(key, InputsPressed, InputThisFrame);
    }
}

std::set<int> InputManager::GetPressedInputs() const
{
    return InputsPressed;
}

std::set<int> InputManager::GetThisFrameInputs() const
{
    return InputThisFrame;
}

bool InputManager::CheckPressedInput(int key)
{
    return InputsPressed.find(key) != InputsPressed.end();
}

bool InputManager::CheckInstantInput(int key)
{
    return InputThisFrame.find(key) != InputThisFrame.end();
}

JoyStickValue InputManager::GetLeftJoyStick() const
{
    return leftJoystick;
}

JoyStickValue InputManager::GetRightJoyStick() const
{
    return rightJoystick;
}

float InputManager::GetLeftTrigger() const
{
    return leftTrigger;
}

float InputManager::GetRightTrigger() const
{
    return rightTrigger;
}

std::string InputManager::InputToString(int inputKey)
{
    if (vkMap.find(inputKey) != vkMap.end())
    {
        return vkMap[inputKey];
    }
    return "Unknown";
}

Vec2 InputManager::GetCursorPos()
{
    double x, y;
    glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
    return Vec2(x, y);
}

std::string InputManager::GetCurrentAbcKey()
{
    return currentAbcKey;
}

void InputManager::ProcessInput(int key, std::set<int>& inputsPressed, std::set<int>& inputsThisFrame)
{
    if (GetAsyncKeyState(key))
    {
        if (!pressed[key])
        {
            //mark as pressed
            pressed[key] = true;
            //add to pressed this frame map only if it wasn't in a pressed state the frame before
            inputsThisFrame.insert(key);
            //add to abecedary
            if (abecedaryMap.find(key) != abecedaryMap.end())
            {
                currentAbcKey = abecedaryMap[key];
            }
        }

        //add to the pressed map
        inputsPressed.insert(key);
    }
    else
    {
        //mark as unpressed
        pressed[key] = false;
    }
}

void InputManager::ProcessInputGamepad(int key, std::set<int>& inputsPressed, std::set<int>& inputsThisFrame)
{
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));

    // Get the state of the first gamepad (0)
    if (XInputGetState(0, &state) == ERROR_SUCCESS)
    {
        // Check if the specified button is pressed
        if ((state.Gamepad.wButtons & key) != 0)
        {
            if (!pressed[key])
            {
                //mark as pressed
                pressed[key] = true;
                //add to pressed this frame map only if it wasn't in a pressed state the frame before
                inputsThisFrame.insert(key);
            }
            //add to the pressed map
            inputsPressed.insert(key);
        }
        else
        {
            //mark as unpressed
            pressed[key] = false;
        }
    }
}

void InputManager::ProcessAxis()
{
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));

    // Get the state of the first gamepad (0)
    if (XInputGetState(0, &state) == ERROR_SUCCESS)
    {
        //left joy stick
        ProcessLeftJoyStick(state);
        //right joy stick
        ProcessRightJoyStick(state);
        //left trigger
        ProcessLeftTrigger(state);
        //right trigger
        ProcessRightTrigger(state);
    }
    //set values to 0
    else
    {
        leftJoystick = JoyStickValue();
        rightJoystick = JoyStickValue();
        leftTrigger = 0;
        rightTrigger = 0;
    }
}

void InputManager::ProcessLeftJoyStick(XINPUT_STATE& state)
{
    float LX = state.Gamepad.sThumbLX;
    float LY = state.Gamepad.sThumbLY;
    //determine how far the controller is pushed
    float magnitude = sqrt(LX * LX + LY * LY);

    //determine the direction the controller is pushed
    float normalizedLX = LX / magnitude;
    float normalizedLY = LY / magnitude;

    float normalizedMagnitude = 0;
    //check if the controller is outside a circular dead zone
    if (magnitude > GAMEPAD_LEFT_THUMB_DEADZONE)
    {
        //clip the magnitude at its expected maximum value
        if (magnitude > 32767) magnitude = 32767;

        //adjust magnitude relative to the end of the dead zone
        magnitude -= GAMEPAD_LEFT_THUMB_DEADZONE;

        //optionally normalize the magnitude with respect to its expected range
        //giving a magnitude value of 0.0 to 1.0
        normalizedMagnitude = magnitude / (32767 - GAMEPAD_LEFT_THUMB_DEADZONE);
    }
    else //if the controller is in the deadzone zero out the magnitude
    {
        magnitude = 0.0;
        normalizedMagnitude = 0.0;
    }

    leftJoystick.direction = Vec2(normalizedLX, -normalizedLY);
    leftJoystick.normalizedMagnitude = normalizedMagnitude;
}

void InputManager::ProcessRightJoyStick(XINPUT_STATE& state)
{
    float RX = state.Gamepad.sThumbRX;
    float RY = state.Gamepad.sThumbRY;

    //determine how far the controller is pushed
    float magnitude = sqrt(RX * RX + RY * RY);

    //determine the direction the controller is pushed
    float normalizedRX = RX / magnitude;
    float normalizedRY = RY / magnitude;

    float normalizedMagnitude = 0;
    //check if the controller is outside a circular dead zone
    if (magnitude > GAMEPAD_RIGHT_THUMB_DEADZONE)
    {
        //clip the magnitude at its expected maximum value
        if (magnitude > 32767) magnitude = 32767;

        //adjust magnitude relative to the end of the dead zone
        magnitude -= GAMEPAD_RIGHT_THUMB_DEADZONE;

        //optionally normalize the magnitude with respect to its expected range
        //giving a magnitude value of 0.0 to 1.0
        normalizedMagnitude = magnitude / (32767 - GAMEPAD_RIGHT_THUMB_DEADZONE);
    }
    else //if the controller is in the deadzone zero out the magnitude
    {
        magnitude = 0.0;
        normalizedMagnitude = 0.0;
    }
    rightJoystick.direction = Vec2(normalizedRX, -normalizedRY);
    rightJoystick.normalizedMagnitude = normalizedMagnitude;
}

void InputManager::ProcessRightTrigger(XINPUT_STATE& state)
{
    float RT = state.Gamepad.bRightTrigger;


    float normalizedMagnitude = 0;
    //check if the controller is outside a circular dead zone
    if (RT > GAMEPAD_TRIGGER_THRESHOLD)
    {
        //clip the magnitude at its expected maximum value
        if (RT > 32767) RT = 32767;

        //adjust magnitude relative to the end of the dead zone
        RT -= GAMEPAD_TRIGGER_THRESHOLD;

        //optionally normalize the magnitude with respect to its expected range
        //giving a magnitude value of 0.0 to 1.0
        normalizedMagnitude = RT / (255 - GAMEPAD_TRIGGER_THRESHOLD);
    }
    else //if the controller is in the deadzone zero out the magnitude
    {
        RT = 0.0;
        normalizedMagnitude = 0.0;
    }

    rightTrigger = normalizedMagnitude;
}

void InputManager::ProcessLeftTrigger(XINPUT_STATE& state)
{
    float LT = state.Gamepad.bLeftTrigger;


    float normalizedMagnitude = 0;
    //check if the controller is outside a circular dead zone
    if (LT > GAMEPAD_TRIGGER_THRESHOLD)
    {
        //clip the magnitude at its expected maximum value
        if (LT > 32767) LT = 32767;

        //adjust magnitude relative to the end of the dead zone
        LT -= GAMEPAD_TRIGGER_THRESHOLD;

        //optionally normalize the magnitude with respect to its expected range
        //giving a magnitude value of 0.0 to 1.0
        normalizedMagnitude = LT / (255 - GAMEPAD_TRIGGER_THRESHOLD);
    }
    else //if the controller is in the deadzone zero out the magnitude
    {
        LT = 0.0;
        normalizedMagnitude = 0.0;
    }

    leftTrigger = normalizedMagnitude;
}
