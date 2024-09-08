#pragma once
#include "../Sprite/Sprite.h"
#include "../Vec2.h"

class DrawDebugUtils
{
public:
    static void DrawDebugPoint(Vec2 pos, Vec2 color);
    static void DrawDebugSquare(Vec2 pos, Vec2 offset, float size, Vec2 color);
    static void DrawDebugRect(Vec2 pos, Vec2 offset, Vec2 size, Vec2 color);
    static void DrawDebugLine(Vec2 start, Vec2 end, Vec2 color);
    static void DrawDebugCircle(Vec2 pos, float radius, Vec2 color);
    static void DrawDebugOval(Vec2 pos, Vec2 size, Vec2 color);
};
