#pragma once
#include "Collider.h"

class PixelsCollider : public Collider
{
    Vec2 m_pixelsSize;
    const uint8_t* m_pixels;

public:
    //constructor
    PixelsCollider(const Vec2* position, Vec2 offset, Vec2 pixelsSize, const uint8_t* pixels);

    //collision
    bool collides(const Collider& other) const override;
    bool collides( Vec2 circlePos, float circleRadius) const override;
    bool collides( Vec2 rectPos, Vec2 rectSize) const override;
    bool collides( Vec2 pixelsPos, Vec2 pixelsSize, const uint8_t* pixels) const override;
};
