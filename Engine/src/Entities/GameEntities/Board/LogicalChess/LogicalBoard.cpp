#include "LogicalBoard.h"

LogicalPiece LogicalBoard::GetCellContent(Vec2 position) const
{
    //check if the given position is inside the board
    if (position.x < 0 || position.x >= 8 || position.y < 0 || position.y >= 8)
    {
        return LogicalPiece(PieceType::OUT_OF_BOUNDS, PieceColor::NO_COLOR);
    }

    //index inside the array
    int index = BOARD_WIDTH * position.x + BOARD_HEIGHT * position.y;
    
    return m_board[index];
}
