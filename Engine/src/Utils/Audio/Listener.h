#pragma once
#include "../Vec2.h"

class Listener
{
private:
    Vec2 m_position, m_velocity, m_orientation;

public:
    Listener();
    void setListenerPosition(Vec2 position);
    void setListenerVelocity(Vec2 velocity);
    void setListenerOrientation(Vec2 orientation);
};
