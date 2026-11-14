#pragma once
#include "LogicalPiece.h"
#include "../../../CoreEntities/Tiles/AlienTileEntity.h"

class LogicalBoard
{
    const int BOARD_WIDTH = 8;
    const int BOARD_HEIGHT = 8;

    //board
    LogicalPiece m_board[64] = {LogicalPiece(PieceType::NONE, NO_COLOR)};

public:
    LogicalBoard();


    // checks if the current state of the board is checkmate
    bool GetIsCheckMate(PieceColor color) const;

    //returns a list with all the pieces of a color that are in imminent danger
    std::vector<LogicalPiece> GetPiecesInDanger(PieceColor color) const;

    //returns the piece at a specific cell
    LogicalPiece GetCellContent(Vec2 position) const;
};
