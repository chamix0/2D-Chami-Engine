#include "Camera.h"

#include "../Engine_Managers/RenderEngine.h"
#include "Audio/Listener.h"

Camera::Camera()
{
    listener = new Listener();
}

Camera::~Camera()
{
    delete listener;
    listener = nullptr;
}

void Camera::UpdateCamera()
{
    m_currentFrameposition = m_nextFrameposition;
}

Vec2 Camera::GetPostion()
{
    return m_currentFrameposition;
}

void Camera::SetPostion(Vec2 newPosition)
{
    //set audio listener position
    listener->setListenerPosition(newPosition);
    m_nextFrameposition = newPosition - RenderEngine::GetInstanceRenderEngine()->GetScreenCenter();
}

Vec2 Camera::ScreenPosToWorld(Vec2 position)
{
    return m_currentFrameposition + position;
}

Vec2 Camera::WorldPosToScreen(Vec2 position)
{
    return position - m_currentFrameposition;
}
