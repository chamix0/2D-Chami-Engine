#pragma once
#include "Vec2.h"

class MathUtils
{
public:
    static float ConvertTo180(float angle);

    /// this function exists because some times 0 are -0 and maps get confused
    /// @param value 
    /// @return 
  static   Vec2 validateZeros(Vec2 value);

    static float Angle0To360(float angle);
    // float GetAngleByDirection360(FVector direction);
    // float GetAngleByDirection180(FVector direction);
    // FVector GetDirectionByAngle(float angle);

    // float GetAngleRelativeToPlayer(FVector playerForward, float angle);
    // bool EqualVector(FVector a, FVector b);
    // bool EqualVector(FVector a, FVector b, float delta);
    static float NormalizeBetweenValues(float value, float min, float max);
    static int GetSign(float value);

    static float Clamp(float value, float min, float max);
    static float Min(float val1, float val2);
    static float Max(float val1, float val2);
    static Vec2 GetCollisionIntersection(const Vec2 rectPos1, const Vec2 rectSize1, const Vec2 rectPos2,
                                         const Vec2 rectSize2);

    static Vec2 Lerp(Vec2 origin, Vec2 destination, float tick, float speed);
    static float fLerp(float origin, float destination, float tick, float speed);
};
