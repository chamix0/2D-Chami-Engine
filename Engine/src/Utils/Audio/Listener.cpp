#include "Listener.h"

#include "AudioBuffer.h"
#include "../MathUtils.h"
#include "../../../openal/AL/al.h"


Listener::Listener(): m_position(Vec2()), m_velocity(Vec2()), m_orientation(Vec2())
{
}

void Listener::setListenerPosition(Vec2 position)
{
 
    m_position = Vec2(-position.x * PIXEL_TO_CM, position.y * PIXEL_TO_CM, m_position.z, m_position.a);
    m_position=MathUtils::validateZeros(m_position);
    alListener3f(AL_POSITION, m_position.x, m_position.y, m_position.z);
    
}

void Listener::setListenerVelocity(Vec2 velocity)
{
    m_velocity = velocity * PIXEL_TO_CM;
    alListener3f(AL_VELOCITY, -velocity.x, velocity.y, velocity.z);
}

void Listener::setListenerOrientation(Vec2 orientation)
{
    m_orientation = orientation * PIXEL_TO_CM;
    alListener3f(AL_ORIENTATION, orientation.x, orientation.y, orientation.z);
}
