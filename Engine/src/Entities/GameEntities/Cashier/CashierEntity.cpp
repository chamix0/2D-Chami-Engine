#include "CashierEntity.h"
#include "../../../Utils/Sprite/Sprite.h"
#include "../../../Engine_Managers/LogicManager.h"
#include "../../../Utils/MathUtils.h"
#include "../Dialogue/DialogueEntity.h"

CashierEntity::CashierEntity(Vec2 position, int renderLayer): Entity(
                                                                  position, renderLayer, "cashier"), m_Player(nullptr)
{
    //machine text
    m_machineText = new Text("data/Fonts/Bubbleboddy.ttf", "Caja", 13, Vec2(0, 1, 0));

    //hint text
    m_hintText = new Text("data/Fonts/pixelFont.ttf", "Presiona Spacio/A", 20, Vec2(0));
    m_machineText->SetPosition(LogicManager::GetInstanceLogicManager()->GetCamera()->WorldPosToScreen(position));
}

CashierEntity::~CashierEntity()
{
    delete m_machineText;
    m_machineText = nullptr;
    delete m_hintText;
    m_hintText = nullptr;
}

void CashierEntity::BeginPlay()
{
    //get player
    m_Player = LogicManager::GetInstanceLogicManager()->GetCurrentScene()->GetPlayer();
}

void CashierEntity::LogicUpdate(double tick)
{
    float distance = m_Player->GetPosition().distance(GetPosition());
    m_machineText->SetPosition(
        LogicManager::GetInstanceLogicManager()->GetCamera()->WorldPosToScreen(GetPosition() + Vec2(-40, -50)));
    m_hintText->SetColor(Vec2(0, 0, 0, 1 - MathUtils::NormalizeBetweenValues(distance, m_minDistance, m_maxDistance)));
    m_hintText->SetPosition(
        LogicManager::GetInstanceLogicManager()->GetCamera()->WorldPosToScreen(GetPosition() + Vec2(-80, 0)));
}

void CashierEntity::InputUpdate(InputManager* input_manager)
{
    if (LogicManager::GetInstanceLogicManager()->GetPaused())
    {
        return;
    }
    if (m_Player->GetPosition().distance(GetPosition()) < m_maxDistance / 2.f)
    {
        bool inputSelect = input_manager->CheckInstantInput(vk_Space) || input_manager->
            CheckInstantInput(GAMEPAD_SOUTH);
        if (inputSelect)
        {
            LogicManager::GetInstanceLogicManager()->SetCurrentScene(
                LogicManager::GetInstanceLogicManager()->GetSceneManager()->GetDialogueLevel(CASHIER_DIALOGUE,
                    m_Player->m_gameData.AllItemsCollected() ? m_Player->m_gameData.GetNumCoins() : -1));
        }
    }
}

void CashierEntity::RenderUpdate()
{
    m_machineText->Draw();
    m_hintText->Draw();
}
