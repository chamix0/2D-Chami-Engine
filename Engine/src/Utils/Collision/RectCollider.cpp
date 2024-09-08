#include "RectCollider.h"

RectCollider::RectCollider(const Vec2* position, Vec2 offset, const Vec2 size): Collider(position, offset),
    m_Size(size)
{
}

bool RectCollider::collides(const Collider& other) const
{
    return other.collides(*m_Position - m_offset, m_Size);
}

bool RectCollider::collides(Vec2 circlePos, float circleRadius) const
{
    return checkCircleRect(circlePos, circleRadius, *m_Position - m_offset, m_Size);
}

bool RectCollider::collides(Vec2 rectPos, Vec2 rectSize) const
{
    return checkRectRect(*m_Position - m_offset, m_Size, rectPos, rectSize);
}

bool RectCollider::collides(Vec2 pixelsPos, Vec2 pixelsSize, const uint8_t* pixels) const
{
    return checkPixelsRect(pixelsPos, pixelsSize, pixels, *m_Position - m_offset, m_Size);
}
