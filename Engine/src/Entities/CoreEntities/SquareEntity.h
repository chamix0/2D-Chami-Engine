#pragma once
#include "../Entity.h"

class SquareEntity : public Entity
{
    Vec2 color;
    Vec2 extents;
    bool moveWithMouse;

public:
    SquareEntity(Vec2 position, Vec2 color, Vec2 extents, bool moveWithMouse = false);

    void LogicUpdate(double tick) override;
    void InputUpdate(InputManager* inputManager) override;
    void RenderUpdate() override;
    void OnCollisionEnter(Entity* otherEntity) override;
    void OnCollisionStay(Entity* otherEntity) override;
    void OnCollisionExit(Entity* otherEntity) override;
    void BeginPlay() override;
    ~SquareEntity() override;
};
