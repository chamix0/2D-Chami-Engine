#include "MathUtils.h"

#include <cmath>

#include "Vec2.h"


float MathUtils::ConvertTo180(float angle)
{
    angle = Angle0To360(angle);

    if (angle > 180)
    {
        angle -= 360;
    }

    return angle;
}

Vec2 MathUtils::validateZeros(Vec2 value)
{
    return Vec2(value.x == 0 ? 0 : value.x, value.y == 0 ? 0 : value.y, value.z == 0 ? 0 : value.z,
                value.a == 0 ? 0 : value.a);
}


float MathUtils::Angle0To360(float angle)
{
    if (angle < 0)
    {
        while (angle < 0)
        {
            angle += 360.f;
        }
    }
    if (angle >= 360)
    {
        while (angle >= 360)
        {
            angle -= 360.f;
        }
    }
    return angle;
}

// float MathUtils::GetAngleByDirection360(Vec2 direction)
// {
// 	return Angle0To360(math::RadiansToDegrees(atan2(direction.x, direction.y)));
// }

// float MathUtils::GetAngleByDirection180(FVector direction)
// {
// 	return ConvertTo180(FMath::RadiansToDegrees(atan2(direction.X, direction.Y)));
// }

// FVector MathUtils::GetDirectionByAngle(float angle)
// {
// 	return FVector(sin(FMath::DegreesToRadians(angle)),
// 	               cos(FMath::DegreesToRadians(angle)),
// 	               0).GetSafeNormal();
// }

// float MathUtils::GetAngleRelativeToPlayer(FVector playerForward, float angle)
// {
// 	float currentActorAngle = MathUtils::Angle0To360(FMath::RadiansToDegrees(atan2(playerForward.X, playerForward.Y)));
// 	angle = Angle0To360(angle);
// 	return MathUtils::ConvertTo180(angle - currentActorAngle);
// }

// bool MathUtils::EqualVector(FVector a, FVector b)
// {
// 	return (a - b).Length() < 0.001f;
// }

// bool MathUtils::EqualVector(FVector a, FVector b, float delta)
// {
// 	return (a - b).Length() < delta;
// }

float MathUtils::NormalizeBetweenValues(float value, float min, float max)
{
    return (value - min) / (max - min);
}

int MathUtils::GetSign(float value)
{
    return value < 0 ? -1 : 1;
}

float MathUtils::Clamp(float value, float min, float max)
{
    if (value < min)
    {
        return min;
    }
    if (value > max)
    {
        return max;
    }
    return value;
}

float MathUtils::Min(float val1, float val2)
{
    return val1 < val2 ? val1 : val2;
}

float MathUtils::Max(float val1, float val2)
{
    return val1 > val2 ? val1 : val2;
}

Vec2 MathUtils::GetCollisionIntersection(const Vec2 rectPos1, const Vec2 rectSize1, const Vec2 rectPos2,
                                         const Vec2 rectSize2)
{
    //rectangle 1
    float r1PositiveX = rectPos1.x + rectSize1.x / 2.f;
    float r1NegativeX = rectPos1.x - rectSize1.x / 2.f;
    float r1PositiveY = rectPos1.y + rectSize1.y / 2.f;
    float r1NegativeY = rectPos1.y - rectSize1.y / 2.f;
    //rectangle 2
    float r2PositiveX = rectPos2.x + rectSize2.x / 2.f;
    float r2NegativeX = rectPos2.x - rectSize2.x / 2.f;
    float r2PositiveY = rectPos2.y + rectSize2.y / 2.f;
    float r2NegativeY = rectPos2.y - rectSize2.y / 2.f;

    //intersection triangle
    float PositiveX = MathUtils::Min(r1PositiveX, r2PositiveX);
    float NegativeX = MathUtils::Max(r1NegativeX, r2NegativeX);
    float PositiveY = MathUtils::Min(r1PositiveY, r2PositiveY);
    float NegativeY = MathUtils::Max(r1NegativeY, r2NegativeY);

    float sizeY = PositiveY - NegativeY;
    float sizeX = PositiveX - NegativeX;
    return Vec2(sizeX, sizeY);
}

Vec2 MathUtils::Lerp(Vec2 origin, Vec2 destination, float tick, float speed)
{
    return origin + (destination - origin) * tick * speed;
}

float MathUtils::fLerp(float origin, float destination, float tick, float speed)
{
    return origin + (destination - origin) * tick * speed;
}

// FVector MathUtils::GetClosestPointToSegment(FVector pos, FVector pointA, FVector pointB)
// {
// 	FRay segment = FRay(pointA, (pointB - pointA).GetSafeNormal());
// 	float segmentLength = (pointA - pointB).Length();
//
// 	FVector closestPoint = segment.ClosestPoint(pos);
// 	closestPoint = (closestPoint - pointA).Length() > segmentLength ? pointB : closestPoint;
// 	return closestPoint;
// }
//
// float MathUtils::GetDistanceToSegment(FVector pos, FVector pointA, FVector pointB)
// {
// 	FVector closestPoint = GetClosestPointToSegment(pos, pointA, pointB);
// 	return (closestPoint - pos).Length();
// }
