#pragma once
#include "GameData.h"
#include "../../Entity.h"

class AudioSource;

class PlayerEntity : public Entity
{
public:
    //game data
    GameData m_gameData;

private:
    float m_playerSpeed = 115.f;
    Vec2 m_direction = Vec2(0);
    Sprite* m_collisionSprite = nullptr;
    Sprite* m_PlayerSpriteFront = nullptr;
    Sprite* m_PlayerSpriteBack = nullptr;
    Sprite* currentSprite = nullptr;
    Sprite* m_lightSprite=nullptr;

 
    float maxFps = 8;

public:
    PlayerEntity(const Vec2& position, int renderLayer);
    ~PlayerEntity() override;
    void InputUpdate(InputManager* input_manager) override;
    void RenderUpdate() override;
    void LogicUpdate(double tick) override;
    void UpdateSpritesDirection(Vec2 direction);
    Vec2 GetPlayerDirection(InputManager* input_manager);
    void OnCollisionEnter(Entity* otherEntity) override;
    void OnCollisionStay(Entity* otherEntity) override;
    void BeginPlay() override;
};
