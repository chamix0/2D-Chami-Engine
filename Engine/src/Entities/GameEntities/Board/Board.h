#pragma once
#include "Cell.h"
#include "../../Entity.h"

class Board : public Entity
{
    std::vector<Cell*> cells; //board cells
    const float CELL_SIZE = 64.f;

public:
    Board();
    ~Board() override;
    void BeginPlay() override;
    // void RenderUpdate() override;

private:
    void CreateBoard();
};
