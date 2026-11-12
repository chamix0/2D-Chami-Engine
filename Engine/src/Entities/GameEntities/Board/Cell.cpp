#include "Cell.h"
#include "../../../Utils/Sprite/Sprite.h"
#include "Enums.h"

Cell::Cell(Vec2 position, Vec2 cellSize, Vec2 color) : Entity(position, 1), m_Color(color)
{
    //create cell sprite
    m_Sprite = new Sprite("data/Sprites/pixel.png", 1, 1,
                          color, BLEND_SOLID, cellSize, Vec2(0.5f, 0.5f), 0.f, CollisionType::NONE, WORLD);
    //init position
    m_Sprite->update(0.f, GetPosition());
    AddSprite(m_Sprite);
}

Cell::~Cell()
{
}

void Cell::Awake()
{
    Entity::Awake();
}

void Cell::BeginPlay()
{
    Entity::BeginPlay();
}

void Cell::LogicUpdate(double tick)
{
    Entity::LogicUpdate(tick);
}

void Cell::InputUpdate(InputManager* input_manager)
{
    Entity::InputUpdate(input_manager);
}

void Cell::RenderUpdate()
{
    Entity::RenderUpdate();

    //draw sprites
    for (Sprite* sprite : m_sprites)
    {
        sprite->draw();
    }
}
