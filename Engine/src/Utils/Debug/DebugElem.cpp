#include "DebugElem.h"

DebugElem::DebugElem(): m_type(DebugType_NONE)
{
}

DebugElem::DebugElem(DebugType type, Vec2 origin, Vec2 offset, Vec2 size, Vec2 endPoint, Vec2 color): m_type(type),
    m_origin(origin), m_offset(offset), m_size(size), m_endPoint(endPoint), m_color(color)
{
}
