#include "CoinEntity.h"
#include "../../../Utils/Sprite/Sprite.h"
#include "Enums.h"
#include "../../../Engine_Managers/AudioManager.h"
#include "../../../Engine_Managers/LogicManager.h"

CoinEntity::CoinEntity(Vec2 pos, int renderLayer): Entity(pos, renderLayer, "coin")
{
    //originasl pos
    m_originalPos = pos;
    //add sprite
    m_coinSprite = new Sprite("data/coin.png", 6, 1, Vec2(1, 1, 1, 1), BLEND_ALPHA,
                            Vec2(1), Vec2(0.5f, 0.5f), 24.f, CollisionType::RECTANGLE);

    AddSprite(m_coinSprite);
}

void CoinEntity::BeginPlay()
{
}

void CoinEntity::LogicUpdate(double tick)
{
    m_frequency += tick;
    SetPosition(m_originalPos + Vec2(0, (sinf(m_frequency) * 10))-10);
    m_coinSprite->update(tick, GetPosition());
}

void CoinEntity::RenderUpdate()
{
    m_coinSprite->draw();
}

void CoinEntity::PickCoin()
{
    //play sound
    AudioManager::GetInstanceAudioManager()->PlayInstantSound("data/Audio/coinSound.wav",1,10,GetPosition());
   
    //mark to delete
    DeleteEntity();
}
