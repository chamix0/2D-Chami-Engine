#pragma once
#include "../../Entity.h"

class GameCameraEntity : public Entity
{
private:
    Entity* target = nullptr;
    float m_speed = 1.f;
    bool reachedTarget = false;
    Vec2 aimOffset;
    float maxAimDistance=75.f;

public:
    GameCameraEntity(Vec2 pos, int rendLayer);
    ~GameCameraEntity() override;
    void BeginPlay() override;
    void LogicLateUpdate(double tick) override;
    void InputUpdate(InputManager* input_manager) override;
};
