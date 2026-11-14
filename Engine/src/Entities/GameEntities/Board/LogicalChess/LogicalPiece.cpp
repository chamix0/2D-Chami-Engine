#include "LogicalPiece.h"

#include "Movement/Movement.h"


LogicalPiece::LogicalPiece() : m_PieceType(PieceType::NONE), m_PieceColor(WHITE)
{
}

LogicalPiece::LogicalPiece(PieceType type, PieceColor pieceColor) : m_PieceType(type), m_PieceColor(pieceColor)
{
}

PieceColor LogicalPiece::GetPieceColor() const
{
    return m_PieceColor;
}

PieceType LogicalPiece::GetPieceType() const
{
    return m_PieceType;
}

std::vector<Movement> LogicalPiece::GetPossibleMoves(Vec2 position, LogicalBoard logicalBoard)
{
    return std::vector<Movement>();
}
