#pragma once
#include "Collider.h"

class RectCollider : public Collider
{
    const Vec2 m_Size;

public:
    //constructor
    RectCollider(const Vec2* position,Vec2 offset, const Vec2 size);
    //collision
    bool collides(const Collider& other) const override;
    bool collides( Vec2 circlePos, float circleRadius) const override;
    bool collides( Vec2 rectPos,  Vec2 rectSize) const override;
    bool collides( Vec2 pixelsPos,  Vec2 pixelsSize, const uint8_t* pixels) const override;
};
