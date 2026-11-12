#pragma once
#include "../../Entity.h"
#include "../Board/Board.h"


class Game : public Entity
{
    
    //playing board
    Board* m_Board = nullptr;

public:
    Game();
    ~Game() override;
    void BeginPlay() override;
};
