#pragma once
#include "../../Entity.h"
#include "../../../Utils/Text/Text.h"
#include "../Player/PlayerEntity.h"

class CashierEntity : public Entity
{
private:
    float m_minDistance = 32.f;
    float m_maxDistance = 150.f;
    
    //machineText
    Text* m_machineText = nullptr;

    //hint  text
    Text* m_hintText = nullptr;
    float m_alpha = 0;
    
    //player reference
    PlayerEntity* m_Player;

public:
    CashierEntity(Vec2 position, int renderLayer);
    ~CashierEntity() override;
    void BeginPlay() override;
    void LogicUpdate(double tick) override;
    void InputUpdate(InputManager* input_manager) override;
    void RenderUpdate() override;
};
