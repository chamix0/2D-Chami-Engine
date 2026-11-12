#include "RegularGameManager.h"
#include "glfw3.h"
#include "../../../Engine_Managers/AudioManager.h"
#include "../../../Engine_Managers/LogicManager.h"
#include "../../../Engine_Managers/RenderEngine.h"


RegularGameManager::RegularGameManager() : Entity(Vec2(0), 0)
{
    //create background
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    //background
    std::vector<Sprite*> m_sprites;
    float backgroundWidth = render_engine->GetScreenWidth();
    float backgroundHeight = render_engine->GetScreenHeight();


    Sprite* BackgroundTile = new Sprite("data/Sprites/pixel.png", 1, 1,
                                        Vec2(165.f / 255.f, 182 / 255.f, 212 / 255.f), BLEND_SOLID,
                                        Vec2(backgroundWidth, backgroundHeight), Vec2(0.5f, 0.5f), 0.f,
                                        CollisionType::NONE, WORLD);
    BackgroundTile->m_position = Vec2(0, 0);
    AddSprite(BackgroundTile);
}


void RegularGameManager::BeginPlay()
{
    Entity::BeginPlay();
    LogicManager* logic_manager = LogicManager::GetInstanceLogicManager();

    //create Game
    m_Game = new Game();
    logic_manager->GetCurrentScene()->AddEntity(m_Game);
}

void RegularGameManager::RenderUpdate()
{
    for (Sprite* sprite : m_sprites)
    {
        sprite->draw();
    }
}
