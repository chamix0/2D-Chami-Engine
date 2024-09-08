#include "PlayerEntity.h"

#include "Enums.h"
#include "../../../Engine_Managers/AudioManager.h"
#include "../../../Engine_Managers/LogicManager.h"
#include "../../../Utils/MathUtils.h"
#include "../../../Utils/Sprite/Sprite.h"
#include "../Coins/CoinEntity.h"

PlayerEntity::PlayerEntity(const Vec2& position, int renderLayer): Entity(position, renderLayer, "Player", true)
{
    m_collisionSprite = new Sprite("data/rect.png", 1, 1, Vec2(0, 0, 1, 1), BLEND_ALPHA,
                                   Vec2(2), Vec2(0.5f, 0.5f), 0.f, CollisionType::RECTANGLE);

    AddSprite(m_collisionSprite);
    m_PlayerSpriteFront = new Sprite("data/Player/playerBack.png", 4, 1, Vec2(1, 1, 1, 1), BLEND_ALPHA,
                                     Vec2(1), Vec2(0.5f, 0.5f), maxFps, CollisionType::NONE);

    AddSprite(m_PlayerSpriteFront);
    m_PlayerSpriteBack = new Sprite("data/Player/playerFront.png", 4, 1, Vec2(1, 1, 1, 1), BLEND_ALPHA,
                                    Vec2(1), Vec2(0.5f, 0.5f), maxFps, CollisionType::NONE);

    m_lightSprite = new Sprite("data/light.png", 1, 1, Vec2(1), BLEND_MUL,
                               Vec2(1), Vec2(0.5f, 0.5f), 0.f, NONE);
    AddSprite(m_lightSprite);

    AddSprite(m_PlayerSpriteBack);
    currentSprite = m_PlayerSpriteFront;
}

PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::InputUpdate(InputManager* input_manager)
{
    Entity::InputUpdate(input_manager);
    if (LogicManager::GetInstanceLogicManager()->GetPaused())
    {
        return;
    }
    //movement
    Vec2 dir = GetPlayerDirection(input_manager);
    m_direction = dir;
}

void PlayerEntity::RenderUpdate()
{
    //player light
    m_lightSprite->draw();

    //normal sprite 
    currentSprite->update(0, m_position - Vec2(0, 16.f));
    currentSprite->draw();

    //reflection Sprite
    currentSprite->DrawScaled(GetPosition() + Vec2(0, 20.f), currentSprite->getScale() * Vec2(1, -1), 0.15f);
}

void PlayerEntity::LogicUpdate(double tick)
{
    Entity::LogicUpdate(tick);

    //update position
    SetPosition(GetPosition() + m_direction * m_playerSpeed * tick, tick);
}

void PlayerEntity::UpdateSpritesDirection(Vec2 direction)
{
    if (direction.y < 0)
    {
        currentSprite = m_PlayerSpriteFront;
    }
    else if (direction.y > 0)
    {
        currentSprite = m_PlayerSpriteBack;
    }

    if (direction.x < 0)
    {
        currentSprite->setScale(Vec2(-abs(currentSprite->getScale().x), currentSprite->getScale().y));
    }
    else if (direction.x > 0)
    {
        currentSprite->setScale(Vec2(abs(currentSprite->getScale().x), currentSprite->getScale().y));
    }

    if (!direction.equals(0))
    {
        currentSprite->setFps(maxFps * direction.Magnitude());
    }
    else
    {
        currentSprite->setFps(0);
    }
}

Vec2 PlayerEntity::GetPlayerDirection(InputManager* input_manager)
{
    //use joystick direction when detected
    if (input_manager->GetLeftJoyStick().normalizedMagnitude > 0)
    {
        Vec2 dir = input_manager->GetLeftJoyStick().direction * input_manager->GetLeftJoyStick().normalizedMagnitude;
        UpdateSpritesDirection(dir);
        return dir;
    }

    //use keyboard as last resource
    Vec2 direction = Vec2(0);

    //get inputs
    bool upInput = input_manager->CheckPressedInput(vk_Up) || input_manager->CheckPressedInput(vk_W);
    bool downInput = input_manager->CheckPressedInput(vk_Down) || input_manager->CheckPressedInput(vk_S);
    bool leftInput = input_manager->CheckPressedInput(vk_Left) || input_manager->CheckPressedInput(vk_A);
    bool rightInput = input_manager->CheckPressedInput(vk_Right) || input_manager->CheckPressedInput(vk_D);

    //vertical axis
    if (upInput)
    {
        direction += Vec2(0, -1);
    }
    else if (downInput)
    {
        direction += Vec2(0, 1);
    }

    //horizontal axis
    if (leftInput)
    {
        direction += Vec2(-1, 0);
    }
    else if (rightInput)
    {
        direction += Vec2(1, 0);
    }

    UpdateSpritesDirection(direction);


    //normalize the value as it may come over 1
    return direction.Normalized();
}

void PlayerEntity::OnCollisionEnter(Entity* otherEntity)
{
    if (otherEntity->GetTag() == "coin")
    {
        CoinEntity* coin = dynamic_cast<CoinEntity*>(otherEntity);
        //pick the coin
        coin->PickCoin();
        //add a coin to game data
        m_gameData.AddCoins(1);
    }
}

void PlayerEntity::OnCollisionStay(Entity* otherEntity)
{
    if (otherEntity->GetTag() == "wall")
    {
        Sprite* optherSprite = otherEntity->GetSprites()[0];
        Vec2 otherSize = optherSprite->getSize() * optherSprite->getScale();
        Vec2 playerSize = m_collisionSprite->getSize() * m_collisionSprite->getScale();

        //rects intersection size
        Vec2 intersection = MathUtils::GetCollisionIntersection(GetPosition(), playerSize, otherEntity->GetPosition(),
                                                                otherSize);
        //position
        float x = GetPosition().x;
        float y = GetPosition().y;

        //when there is no intersection retutn
        if (intersection.equals())
        {
            return;
        }

        //find what side to collide and clamp collision
        if (intersection.x > intersection.y)
        {
            int sign = GetPosition().y < otherEntity->GetPosition().y ? -1 : 1;
            y = otherEntity->GetPosition().y + sign * ((otherSize.y / 2.f) + (playerSize.y / 2.f));
        }
        else
        {
            int sign = GetPosition().x < otherEntity->GetPosition().x ? -1 : 1;
            x = otherEntity->GetPosition().x + sign * ((otherSize.x / 2.f) + (playerSize.x / 2.f));
        }

        SetPosition(Vec2(x, y));
    }
}

void PlayerEntity::BeginPlay()
{
    Entity::BeginPlay();
}
