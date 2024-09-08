#pragma once
#include "../../Entity.h"
#include "../../../Utils/Audio/AudioSource.h"

class CoinEntity : public Entity
{
private:
    Sprite* m_coinSprite = nullptr;
    float m_frequency = 0;
    Vec2 m_originalPos;

public:
    CoinEntity(Vec2 pos, int renderLayer);
    void BeginPlay() override;
    void LogicUpdate(double tick) override;
    void RenderUpdate() override;
    void PickCoin();
};
