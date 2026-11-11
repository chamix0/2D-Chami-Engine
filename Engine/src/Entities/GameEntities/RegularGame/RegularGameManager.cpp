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
                                        Vec2(1), BLEND_SOLID,
                                        Vec2(backgroundWidth, backgroundHeight), Vec2(0.f, 0.f), 0.f,
                                        CollisionType::NONE, UI);
    BackgroundTile->m_position = Vec2(0, 0);
    AddSprite(BackgroundTile);
}

void RegularGameManager::BeginPlay()
{
    Entity::BeginPlay();
}

void RegularGameManager::RenderUpdate()
{
    for (Sprite* sprite : m_sprites)
    {
        sprite->draw();
    }
}
