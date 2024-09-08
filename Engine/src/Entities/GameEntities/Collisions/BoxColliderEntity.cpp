#include "BoxColliderEntity.h"
#include "../../../Utils/Sprite/Sprite.h"

BoxColliderEntity::BoxColliderEntity(const Vec2& position, Vec2 size, std::string tag):
    Entity(position, 20, tag, false), m_size(size)
{
    m_sprite = new Sprite("data/collision.png", 1, 1, Vec2(0,0,0,0), BLEND_ALPHA, size, Vec2(0.5f), 0, RECTANGLE,
                          WORLD, 0);
    m_sprite->update(0, position);
    AddSprite(m_sprite);
}

void BoxColliderEntity::LogicUpdate(double tick)
{
    m_sprite->update(0, GetPosition());
}

void BoxColliderEntity::RenderUpdate()
{
    m_sprite->draw();
}
