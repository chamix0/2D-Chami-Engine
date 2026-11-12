#include "Game.h"

#include "../../../Engine_Managers/LogicManager.h"
#include "../../../Scenes/SceneManager.h"

Game::Game() : Entity(Vec2(0, 0))
{

}

Game::~Game()
{
    //the scene will delete the board entity
}

void Game::BeginPlay()
{
    Entity::BeginPlay();
    
    LogicManager* logic_manager = LogicManager::GetInstanceLogicManager();

    //create board entity
    m_Board = new Board();
    logic_manager->GetCurrentScene()->AddEntity(m_Board);
}
