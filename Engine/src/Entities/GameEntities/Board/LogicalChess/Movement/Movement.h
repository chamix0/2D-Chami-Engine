#pragma once
#include "../LogicalPiece.h"
#include "../../../../../Utils/Vec2.h"

class Movement
{
    Vec2 FromPosition;
    Vec2 ToPosition;
    LogicalPiece MovedPiece;
    LogicalPiece CapturedPiece;

public:
    Movement(Vec2 _FromPosition, Vec2 _ToPosition, LogicalPiece _MovedPiece, LogicalPiece _CapturedPiece);
};
