#pragma once
#include <vector>

#include "LogicalBoard.h"
#include "../../../../Utils/Vec2.h"
#include "../../../../Utils/GameUtils/MyEnums.h"

class Movement;

class LogicalPiece
{
    PieceColor m_PieceColor;
    PieceType m_PieceType = PieceType::NONE;

public:
    LogicalPiece();
    LogicalPiece(PieceType type, PieceColor pieceColor);

    PieceColor GetPieceColor() const;
    PieceType GetPieceType() const;

    /// Gives a list of the base moves this piece have
    /// @return 
    virtual std::vector<Movement> GetPossibleMoves(Vec2 position, LogicalBoard logicalBoard);
};
