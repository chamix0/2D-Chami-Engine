#pragma once

enum ObserverEvents
{
    GAME_SAVED,
    ObserverEvents_COUNT
};

enum PieceColor
{
    WHITE, BLACK,NO_COLOR,
    COLOR_COUNT
};

enum PieceType
{
    KING, QUEEN, BISHOP, ROOK, KNIGHT, PAWN, NONE, OUT_OF_BOUNDS
};
