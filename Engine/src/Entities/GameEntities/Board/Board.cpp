#include "Board.h"

#include "../../../Engine_Managers/LogicManager.h"

Board::Board() : Entity(Vec2(0.0f, 0.0f))
{
}

Board::~Board()
{
}

void Board::BeginPlay()
{
    Entity::BeginPlay();

    //create board
    CreateBoard();
}

void Board::CreateBoard()
{
    LogicManager* logicManager = LogicManager::GetInstanceLogicManager();
    //background
    std::vector<Sprite*> m_sprites;
    float halfTileSize = CELL_SIZE / 2.f;
    int numSquaresWidth = 8;
    int numSquaresHeight = 8;

    Vec2 colorWhite = Vec2(1);
    Vec2 colorBlack = Vec2(43.f / 255.f, 47 / 255.f, 51 / 255.f);

    Vec2 offset = Vec2(CELL_SIZE * numSquaresWidth / 2.f, CELL_SIZE * numSquaresHeight / 2.f);

    for (int x = 0; x < numSquaresWidth; ++x)
    {
        for (int y = 0; y < numSquaresHeight; ++y)
        {
            int color = x % 2 == 0 ? 0 : 1;
            color = y % 2 == 0 ? color : (color + 1) % 2;
            Vec2 position = Vec2(CELL_SIZE * x + halfTileSize, CELL_SIZE * y + halfTileSize)-offset;
            Cell* cell = new Cell(position, CELL_SIZE, Vec2(color == 0 ? colorWhite : colorBlack));
            logicManager->GetCurrentScene()->AddEntity(cell);
            cells.push_back(cell);
        }
    }
}
