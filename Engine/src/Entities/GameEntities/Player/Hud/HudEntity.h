#pragma once
#include "../PlayerEntity.h"
#include "../../../Entity.h"

class Text;

class HudEntity : public Entity
{
private:
    //player reference
    PlayerEntity* m_playerEntity;

    bool paused = false;
    
    //ticket
    Sprite* ticketSprite;
    Text* ticketText;
    Text* pauseText;

    bool isOut = false;
    float ticketDesiredPos;
    float m_hiddenPos;

    //coin counter
    Sprite* coinSprite;
    Text* coinsText;

public:
    HudEntity(const Vec2& position, int renderLayer);
    ~HudEntity() override;

    void BeginPlay() override;
    void InputUpdate(InputManager* input_manager) override;
    void RenderUpdate() override;
    void LogicUpdate(double tick) override;
};
