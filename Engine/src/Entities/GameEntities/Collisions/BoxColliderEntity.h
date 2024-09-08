#pragma once
#include "../../Entity.h"

class BoxColliderEntity : public Entity
{
private:
    Sprite* m_sprite;
    Vec2 m_size;

public:
    BoxColliderEntity(const Vec2& position, Vec2 size, std::string tag);
    void LogicUpdate(double tick) override;
    void RenderUpdate() override;
};
