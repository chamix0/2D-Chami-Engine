#include "Collider.h"

#include <cmath>

#include "litegfx.h"
#include "../MathUtils.h"
#include "../Debug/DrawDebugUtils.h"

Collider::Collider(const Vec2* position, Vec2 offset): m_Position(position), m_offset(offset)
{
}

Collider::~Collider() = default;


bool Collider::checkCircleCircle(const Vec2 pos1, float radius1, const Vec2 pos2, float radius2) const
{
    //dir to pos2
    float dist = (pos2 - pos1).Magnitude();
    return dist <= (radius1 + radius2);
}

bool Collider::checkCircleRect(const Vec2 circlePos, float circleRadius, const Vec2 rectPos,
                               const Vec2 rectSize) const
{
    //rectangle 
    float PositiveX = rectPos.x + rectSize.x;
    float NegativeX = rectPos.x;
    float PositiveY = rectPos.y + rectSize.y;
    float NegativeY = rectPos.y;

    //closest point of the rectangle to the circle
    float closestX = MathUtils::Clamp(circlePos.x, NegativeX, PositiveX);
    float closestY = MathUtils::Clamp(circlePos.y, NegativeY, PositiveY);

    //distance to the closest point
    Vec2 closestPoint(closestX, closestY);
    float dist = (closestPoint - circlePos).Magnitude();

    return dist <= circleRadius;
}

bool Collider::checkRectRect(const Vec2 rectPos1, const Vec2 rectSize1, const Vec2 rectPos2,
                             const Vec2 rectSize2) const
{
    //rectangle 1
    float r1PositiveX = rectPos1.x + rectSize1.x;
    float r1NegativeX = rectPos1.x;
    float r1PositiveY = rectPos1.y + rectSize1.y;
    float r1NegativeY = rectPos1.y;

    //rectangle 2
    float r2PositiveX = rectPos2.x + rectSize2.x;
    float r2NegativeX = rectPos2.x;
    float r2PositiveY = rectPos2.y + rectSize2.y;
    float r2NegativeY = rectPos2.y;
    bool collides = (r1PositiveX >= r2NegativeX) &&
        (r1NegativeX <= r2PositiveX) &&
        (r1PositiveY >= r2NegativeY) &&
        (r1NegativeY <= r2PositiveY);
    return collides;
}

bool Collider::checkCirclePixels(const Vec2 circlePos, float circleRadius, const Vec2 pixelsPos,
                                 const Vec2 pixelsSize, const uint8_t* pixels) const
{
    for (int y = 0; y < pixelsSize.y; ++y)
    {
        for (int x = 0; x < pixelsSize.x; ++x)
        {
            int index = (y * pixelsSize.x) + (x);
            uint8_t pixel = pixels[index * 4 + 3];
            float dist = (Vec2(x + pixelsPos.x, y + pixelsPos.y) - circlePos).Magnitude();

            if (pixel != 0 && dist <= circleRadius)
            {
                return true;
            }
        }
    }
    return false;
}

bool Collider::checkPixelsPixels(Vec2 pixelsPos1, Vec2 pixelsSize1, const uint8_t* pixels1, Vec2 pixelsPos2,
                                 Vec2 pixelsSize2,
                                 const uint8_t* pixels2) const
{
    if (pixels1 == nullptr || pixels2 == nullptr)
    {
        return false;
    }

    //rectangle 1
    float r1PositiveX = pixelsPos1.x + pixelsSize1.x;
    float r1NegativeX = pixelsPos1.x;
    float r1PositiveY = pixelsPos1.y + pixelsSize1.y;
    float r1NegativeY = pixelsPos1.y;
    //rectangle 2
    float r2PositiveX = pixelsPos2.x + pixelsSize2.x;
    float r2NegativeX = pixelsPos2.x;
    float r2PositiveY = pixelsPos2.y + pixelsSize2.y;
    float r2NegativeY = pixelsPos2.y;

    if (checkRectRect(pixelsPos1, pixelsSize1, pixelsPos2, pixelsSize2))
    {
        //intersection triangle
        float PositiveX = MathUtils::Min(r1PositiveX, r2PositiveX);
        float NegativeX = MathUtils::Max(r1NegativeX, r2NegativeX);
        float PositiveY = MathUtils::Min(r1PositiveY, r2PositiveY);
        float NegativeY = MathUtils::Max(r1NegativeY, r2NegativeY);

        float sizeY = PositiveY - NegativeY;
        float sizeX = PositiveX - NegativeX;

        Vec2 topLeftCorner = Vec2(NegativeX, NegativeY);

        // Verificar pixel por pixel en la region de interseccion
        for (int y = static_cast<int>(topLeftCorner.y); y < static_cast<int>(topLeftCorner.y + sizeY); ++y)
        {
            for (int x = static_cast<int>(topLeftCorner.x); x < static_cast<int>(topLeftCorner.x + sizeX); ++x)
            {
                // Coordenadas locales dentro de la textura
                int xLocal1 = x - pixelsPos1.x;
                int yLocal1 = y - pixelsPos1.y;
                int index1 = (yLocal1 * pixelsSize1.x + xLocal1);
                uint8_t pix1 = pixels1[index1 * 4 + 3];

                // Coordenadas locales dentro de la textura
                int xLocal2 = x - pixelsPos2.x;
                int yLocal2 = y - pixelsPos2.y;
                int index2 = (yLocal2 * pixelsSize2.x + xLocal2);
                uint8_t pix2 = pixels2[index2 * 4 + 3];

                // Verificar si el pixel no es transparente
                if (pix1 != 0 && pix2 != 0)
                {
                    // DrawDebugUtils::DrawDebugPoint(Vec2(x, y), Vec2(0, 1, 0, 0.5f));
                    return true;
                }
            }
        }
    }
    return false;
}

bool Collider::checkPixelsRect(Vec2 pixelsPos, Vec2 pixelsSize, const uint8_t* pixels, Vec2 rectPos,
                               Vec2 rectSize) const
{
    //rectangle 1
    float r1PositiveX = pixelsPos.x + pixelsSize.x;
    float r1NegativeX = pixelsPos.x;
    float r1PositiveY = pixelsPos.y + pixelsSize.y;
    float r1NegativeY = pixelsPos.y;
    //rectangle 2
    float r2PositiveX = rectPos.x + rectSize.x;
    float r2NegativeX = rectPos.x;
    float r2PositiveY = rectPos.y + rectSize.y;
    float r2NegativeY = rectPos.y;

    if (checkRectRect(pixelsPos, pixelsSize, rectPos, rectSize))
    {
        //intersection rectangle
        float PositiveX = MathUtils::Min(r1PositiveX, r2PositiveX);
        float NegativeX = MathUtils::Max(r1NegativeX, r2NegativeX);
        float PositiveY = MathUtils::Min(r1PositiveY, r2PositiveY);
        float NegativeY = MathUtils::Max(r1NegativeY, r2NegativeY);

        float sizeY = (PositiveY - NegativeY);
        float sizeX = (PositiveX - NegativeX);

        Vec2 topLeftCorner1 = Vec2(NegativeX, NegativeY);
        // DrawDebugUtils::DrawDebugRect(pixelsPos, Vec2(), pixelsScale, Vec2(0, 1, 1, 0.5f));
        // DrawDebugUtils::DrawDebugRect(topLeftCorner1, Vec2(), Vec2(sizeX, sizeY), Vec2(0, 1, 0, 0.5f));

        for (int y = static_cast<int>(topLeftCorner1.y); y < static_cast<int>(topLeftCorner1.y + sizeY); ++y)
        {
            for (int x = static_cast<int>(topLeftCorner1.x); x < static_cast<int>(topLeftCorner1.x + sizeX); ++x)
            {
                int xLocal = x - pixelsPos.x;
                int yLocal = y - pixelsPos.y;
                int index = (yLocal * pixelsSize.x + xLocal);

                if (pixels[index * 4 + 3] != 0)
                {
                    // DrawDebugUtils::DrawDebugPoint(Vec2(x, y), Vec2(0, 1, 0, 0.5f));
                    return true;
                }
            }
        }
    }
    return false;
}
