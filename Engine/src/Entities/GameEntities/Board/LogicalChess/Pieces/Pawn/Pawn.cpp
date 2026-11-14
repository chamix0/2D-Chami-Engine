#include "Pawn.h"

#include "../../Movement/Movement.h"

Pawn::Pawn(PieceColor pieceColor) : LogicalPiece(PAWN, pieceColor)
{
    
}

std::vector<Movement> Pawn::GetPossibleMoves(Vec2 position, LogicalBoard logicalBoard)
{
    std::vector<Movement> possibleMoves;

    int direction = GetPieceColor() == WHITE ? -1 : 1;
    int initialRow = GetPieceColor() == WHITE ? 6 : 1;

    //front cell, front cell is empty
    Vec2 checkingPosition = position + Vec2(0, 1 * direction);
    LogicalPiece frontCellContent = logicalBoard.GetCellContent(checkingPosition);
    if (frontCellContent.GetPieceType() == PieceType::NONE)
    {
        possibleMoves.push_back(Movement(position, checkingPosition, this, frontCellContent));
    }

    //initial movement, front cell is empty as well as the next one
    checkingPosition = position + Vec2(0, 2 * direction);
    LogicalPiece nextFrontCellContent = logicalBoard.GetCellContent(checkingPosition);
    if (position.y == initialRow &&
        frontCellContent.GetPieceType() == PieceType::NONE &&
        nextFrontCellContent.GetPieceType() == PieceType::NONE)
    {
        possibleMoves.push_back(Movement(position, checkingPosition, this, nextFrontCellContent));
    }

    //diagonal attack right
    for (int i = -1; i <= 1; i += 2)
    {
        checkingPosition = position + Vec2(i, 1 * direction);
        LogicalPiece DiagonalCellContent = logicalBoard.GetCellContent(checkingPosition);
        if (DiagonalCellContent.GetPieceType() != PieceType::NONE && DiagonalCellContent.GetPieceType() !=
            PieceType::OUT_OF_BOUNDS && DiagonalCellContent.GetPieceColor() != GetPieceColor())
        {
            possibleMoves.push_back(Movement(position, checkingPosition, this, DiagonalCellContent));
        }
    }
    
    
    return possibleMoves;
}
