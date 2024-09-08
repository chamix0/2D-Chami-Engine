#pragma once
#include "../../Utils/Vec2.h"

struct JoyStickValue
{
    Vec2 direction=Vec2();
    float normalizedMagnitude = 0;
    JoyStickValue();
};
