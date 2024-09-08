#include "Entity.h"

#include "../Engine_Managers/LogicManager.h"
#include "../Utils/Collision/CircleCollider.h"
#include "../Utils/Collision/PixelsCollider.h"
#include "../Utils/Collision/RectCollider.h"
#include "../Utils/Sprite/Sprite.h"


Entity::Entity(Vec2 position, int renderLayer, std::string tag, bool CheckCollision): m_renderLayer(renderLayer),
    m_tag(tag), m_position(position), m_checkCollision(CheckCollision)
{
}

Entity::~Entity()
{
    for (Sprite* sprite : m_sprites)
    {
        delete sprite;
        sprite = nullptr;
    }
}


Vec2 Entity::GetPosition() const
{
    return m_position;
}

void Entity::SetPosition(Vec2 pos, float tick)
{
    m_position = pos;

    //update sprites position
    for (int i = 0; i < m_sprites.size(); ++i)
    {
        m_sprites[i]->update(tick, pos);
    }
}

int Entity::GetRenderLayer() const
{
    return m_renderLayer;
}

void Entity::Awake()
{
}

void Entity::BeginPlay()
{
}

void Entity::EarlyUpdate(double tick)
{
}

void Entity::LogicUpdate(double tick)
{
    if (m_checkCollision)
    {
        LogicManager::GetInstanceLogicManager()->UpdateCollisions(this);
    }
}

void Entity::LogicLateUpdate(double tick)
{
}

void Entity::InputUpdate(InputManager* input_manager)
{
    
}

void Entity::OnCollisionEnter(Entity* otherEntity)
{
}

void Entity::OnCollisionStay(Entity* otherEntity)
{
}

void Entity::OnCollisionExit(Entity* otherEntity)
{
}

void Entity::RenderUpdate()
{
}

void Entity::AddSprite(Sprite* sprite)
{
    m_sprites.push_back(sprite);
}

void Entity::RemoveSprite(Sprite* sprite)
{
    std::vector<Sprite*> aux;
    for (Sprite* elem : m_sprites)
    {
        if (elem != sprite)
        {
            m_sprites.push_back(elem);
        }
        else
        {
            delete elem;
            elem = nullptr;
        }
    }
    m_sprites = aux;
}

std::vector<Sprite*> Entity::GetSprites()
{
    return m_sprites;
}


bool Entity::Collides(Entity* otherEntity)
{
    for (int i = 0; i < otherEntity->GetSprites().size(); ++i)
    {
        for (int j = 0; j < m_sprites.size(); ++j)
        {
            if (otherEntity->GetSprites()[i]->collides(*m_sprites[j]))
            {
                return true;
            }
        }
    }
    return false;
}


void Entity::DeleteEntity()
{
    m_hasToBeDeleted = true;
}

bool Entity::HasToBeDeleted() const
{
    return m_hasToBeDeleted;
}

bool Entity::GetCheckCollision()
{
    return m_checkCollision;
}

void Entity::SetCheckCollision(bool value)
{
    m_checkCollision = value;
}

bool Entity::HasCollision()
{
    for (int i = 0; i < m_sprites.size(); ++i)
    {
        if (m_sprites[i]->collisionType != NONE)
        {
            return true;
        }
    }
    return false;
}

bool Entity::GetColliding(Entity* entity)
{
    // not found
    if (m_collisionEntities.find(entity) == m_collisionEntities.end())
    {
        m_collisionEntities[entity] = false;
    }
    return m_collisionEntities[entity];
}

void Entity::SetColliding(Entity* entity, bool value)
{
    m_collisionEntities[entity] = value;
}

std::string Entity::GetTag() const
{
    return m_tag;
}
