#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
private:
    const float m_circleRadius;

public:
    //contructor
    CircleCollider(const Vec2* position, Vec2 offset, float radius);

    //collision 
    bool collides(const Collider& other) const override;
    bool collides(Vec2 circlePos, float circleRadius) const override;
    bool collides(Vec2 rectPos,  Vec2 rectSize) const override;
    bool collides(Vec2 pixelsPos,  Vec2 pixelsSize, const uint8_t* pixels) const override;
};

