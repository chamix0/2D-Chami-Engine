#pragma once
#include "Vec2.h"

class Listener;

class Camera
{
public:
    Camera();
    ~Camera();
    Vec2 m_currentFrameposition;
    Vec2 m_nextFrameposition;
    Listener* listener=nullptr;
    
    void UpdateCamera();
    Vec2 GetPostion();
    void SetPostion(Vec2 newPosition);
    Vec2 WorldPosToScreen(Vec2 position);
    Vec2 ScreenPosToWorld(Vec2 position);
};
