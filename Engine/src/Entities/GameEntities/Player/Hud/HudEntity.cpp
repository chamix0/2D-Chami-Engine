#include "HudEntity.h"

#include "../../../../Engine_Managers/RenderEngine.h"
#include "../../../../Engine_Managers/LogicManager.h"
#include "../../../../Utils/MathUtils.h"
#include "../../../../Utils/Sprite/Sprite.h"
#include "../../../../Utils/Text/Text.h"

HudEntity::HudEntity(const Vec2& position, int renderLayer): Entity(position, renderLayer, "HUD")
{
    //ticket
    //create sprite
    ticketSprite = new Sprite("data/Game/UI/SettingPannel.png", 2, 1, Vec2(1), BLEND_ALPHA, Vec2(2), Vec2(1), 0,
                              NONE, UI, 1);
    //init hidden position
    m_hiddenPos = RenderEngine::GetInstanceRenderEngine()->GetScreenHeight() + ticketSprite->size.y * ticketSprite->
        scale.y - 60.f;
    ticketSprite->update(0, Vec2(RenderEngine::GetInstanceRenderEngine()->GetScreenWidth(), m_hiddenPos));
    ticketDesiredPos = m_hiddenPos;
    //add sprite to entity
    AddSprite(ticketSprite);
    //init text
    ticketText = new Text("data/Fonts/pixelFont.ttf", "Lista de la compra", 22, Vec2(0));

    //pause text
    pauseText = new Text("data/Fonts/pixelFont.ttf", "PAUSA", 50, Vec2(0));
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    pauseText->SetPosition(render_engine->GetScreenCenter() + Vec2(-90, 10));

    //coin
    coinSprite = new Sprite("data/coin.png", 6, 1, Vec2(1), BLEND_ALPHA, Vec2(1), Vec2(0), 0, NONE, UI);
    coinSprite->update(0, Vec2(10.f));
    AddSprite(coinSprite);
    coinsText = new Text("data/Fonts/pixelFont.ttf", "0", 30, Vec2(1));
    coinsText->SetPosition(Vec2(50.f, 35.f));
}

HudEntity::~HudEntity()
{
    delete ticketText;
    ticketText = nullptr;
    delete coinsText;
    coinsText = nullptr;
    delete pauseText;
    pauseText = nullptr;
}

void HudEntity::BeginPlay()
{
    //get player
    std::vector<Entity*> found = LogicManager::GetInstanceLogicManager()->FindEntitiesWithTag("Player");
    if (found.size() > 0)
    {
        m_playerEntity = dynamic_cast<PlayerEntity*>(found[0]);
    }
}

void HudEntity::InputUpdate(InputManager* input_manager)
{
    bool ticketInput = input_manager->CheckInstantInput(vk_Tab) || input_manager->
        CheckInstantInput(GAMEPAD_DPAD_UP);
    bool pauseInput = input_manager->CheckInstantInput(vk_Escape) || input_manager->CheckInstantInput(vk_P) ||
        input_manager->
        CheckInstantInput(GAMEPAD_START);

    if (pauseInput)
    {
        paused = !paused;
        if (paused)
        {
            LogicManager::GetInstanceLogicManager()->SetPause(true);
        }
        else
        {
            LogicManager::GetInstanceLogicManager()->SetPause(false);
        }
    }

    if (ticketInput)
    {
        isOut = !isOut;
        ticketDesiredPos = isOut ? RenderEngine::GetInstanceRenderEngine()->GetScreenHeight() : m_hiddenPos;
    }
}

void HudEntity::RenderUpdate()
{
    if (paused)
    {
        ticketSprite->DrawScaled(Vec2(1000), Vec2(10), 0.25f);
        pauseText->Draw();
        return;
    }

    //coin
    coinSprite->draw();
    coinsText->Draw();

    //ticket
    ticketSprite->draw();
    ticketText->Draw();
}

void HudEntity::LogicUpdate(double tick)
{
    //coin
    coinsText->SetText(std::to_string(m_playerEntity->m_gameData.GetNumCoins()));

    //ticket
    Vec2 ticketPos = Vec2(RenderEngine::GetInstanceRenderEngine()->GetScreenWidth(),
                          MathUtils::fLerp(ticketSprite->m_position.y, ticketDesiredPos, tick, 10.f));
    ticketSprite->update(0, ticketPos);
    ticketText->SetText(std::string("Lista de la compra|").append(m_playerEntity->m_gameData.GetItemsString()));
    ticketText->SetPosition(ticketPos - Vec2(220.f, 234));
}
