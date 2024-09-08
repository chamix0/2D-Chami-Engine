#include "PixelsCollider.h"

PixelsCollider::PixelsCollider(const Vec2* position, Vec2 offset, Vec2 pixelsSize,
                               const uint8_t* pixels):
    Collider(position, offset),
    m_pixelsSize(pixelsSize), m_pixels(pixels)
{
}

bool PixelsCollider::collides(const Collider& other) const
{
    return other.collides(*m_Position - m_offset, m_pixelsSize, m_pixels);
}

bool PixelsCollider::collides(Vec2 circlePos, float circleRadius) const
{
    return checkCirclePixels(circlePos, circleRadius, *m_Position - m_offset, m_pixelsSize, m_pixels);
}

bool PixelsCollider::collides(Vec2 rectPos, Vec2 rectSize) const
{
    return checkPixelsRect(*m_Position - m_offset, m_pixelsSize, m_pixels, rectPos, rectSize);
}

bool PixelsCollider::collides(Vec2 pixelsPos, Vec2 pixelsSize,
                              const uint8_t* pixels) const
{
    return checkPixelsPixels(*m_Position - m_offset, m_pixelsSize, m_pixels, pixelsPos, pixelsSize,
                             pixels);
}
