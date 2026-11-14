#pragma once
#include "../../LogicalPiece.h"


class Movement;

class Pawn : public LogicalPiece
{
    
public:
    Pawn(PieceColor pieceColor);
    
    std::vector<Movement> GetPossibleMoves(Vec2 position, LogicalBoard logicalBoard) override;
    
    
};
