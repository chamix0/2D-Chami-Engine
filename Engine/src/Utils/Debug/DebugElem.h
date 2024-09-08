#pragma once
#include "../Vec2.h"

enum DebugType
{
    DebugType_SQUARE,
    DebugType_RECTANGLE,
    DebugType_POINT,
    DebugType_LINE,
    DebugType_CIRCLE,
    DebugType_OVAL,
    DebugType_NONE
};

class DebugElem
{
public:
    Vec2 m_origin;
    Vec2 m_offset;
    Vec2 m_size;
    Vec2 m_endPoint;
    Vec2 m_color;
    DebugType m_type;
    DebugElem();
    DebugElem(DebugType type, Vec2 origin, Vec2 offset, Vec2 size, Vec2 endPoint, Vec2 color);
};
