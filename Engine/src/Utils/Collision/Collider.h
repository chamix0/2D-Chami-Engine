#pragma once
#include <cstdint>

#include "../Vec2.h"

enum CollisionType
{
    CIRCLE,
    RECTANGLE,
    PIXEL,
    NONE
};

class Collider
{
protected:
    const Vec2* m_Position;
    const Vec2 m_offset;

public:
    Collider(const Vec2* postion, Vec2 offset);
    virtual ~Collider();
    virtual bool collides(const Collider& other) const =0;
    virtual bool collides(Vec2 circlePos, float circleRadius) const =0;
    virtual bool collides(Vec2 rectPos, Vec2 rectSize) const =0;
    virtual bool collides(Vec2 pixelsPos, Vec2 pixelsSize, const uint8_t* pixels) const =0;

protected:
    bool checkCircleCircle(Vec2 pos1, float radius1, Vec2 pos2, float radius2) const;
    bool checkCircleRect(Vec2 circlePos, float circleRadius, Vec2 rectPos, Vec2 rectSize) const;
    bool checkRectRect(Vec2 rectPos1, Vec2 rectSize1, Vec2 rectPos2, Vec2 rectSize2) const;
    bool checkCirclePixels(Vec2 circlePos, float circleRadius, Vec2 pixelsPos, Vec2 pixelsSize,
                           const uint8_t* pixels) const;
    bool checkPixelsPixels(Vec2 pixelsPos1, Vec2 pixelsSize1, const uint8_t* pixels1, Vec2 pixelsPos2, Vec2 pixelsSize2,
                           const uint8_t* pixels2) const;
    bool checkPixelsRect(Vec2 pixelsPos, Vec2 pixelsSize, const uint8_t* pixels, Vec2 rectPos, Vec2 rectSize) const;
};
