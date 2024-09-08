#include "CircleCollider.h"

CircleCollider::CircleCollider(const Vec2* position, Vec2 offset, float radius): Collider(position, offset),
    m_circleRadius(radius)
{
}

bool CircleCollider::collides(const Collider& other) const
{
    return other.collides(*m_Position - m_offset + Vec2(m_circleRadius, m_circleRadius), m_circleRadius);
}

bool CircleCollider::collides(Vec2 circlePos, float circleRadius) const
{
    return checkCircleCircle(*m_Position - m_offset + Vec2(m_circleRadius, m_circleRadius), m_circleRadius, circlePos,
                             circleRadius);
}

bool CircleCollider::collides(Vec2 rectPos, Vec2 rectSize) const
{
    return checkCircleRect(*m_Position - m_offset + Vec2(m_circleRadius, m_circleRadius), m_circleRadius, rectPos,
                           rectSize);
}

bool CircleCollider::collides(Vec2 pixelsPos, Vec2 pixelsSize, const uint8_t* pixels) const
{
    return checkCirclePixels(*m_Position - m_offset + Vec2(m_circleRadius, m_circleRadius), m_circleRadius, pixelsPos,
                             pixelsSize, pixels);
}
