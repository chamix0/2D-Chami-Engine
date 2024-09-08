#include "GameCameraEntity.h"
#include "../../../Utils/Camera.h"
#include "../../../Engine_Managers/LogicManager.h"
#include "../../../Utils/MathUtils.h"

GameCameraEntity::GameCameraEntity(Vec2 pos, int rendLayer): Entity(pos, rendLayer,"camera")
{
}

GameCameraEntity::~GameCameraEntity()
{
}

void GameCameraEntity::BeginPlay()
{
    target = LogicManager::GetInstanceLogicManager()->GetCurrentScene()->GetPlayer();

    if (target != nullptr)
    {
        //update entity position
        SetPosition(target->GetPosition());

        //update camera position
        Camera* cam = LogicManager::GetInstanceLogicManager()->GetCamera();
        cam->SetPostion(target->GetPosition());
    }
    else
    {
        m_position = Vec2();
        Camera* cam = LogicManager::GetInstanceLogicManager()->GetCamera();
        cam->SetPostion(m_position);
    }
}

void GameCameraEntity::LogicLateUpdate(double tick)
{
    // Entity::LogicLateUpdate(tick);

    if (target == nullptr)
    {
        return;
    }

    Vec2 targetPos = target->GetPosition();
    Vec2 direction = (targetPos - GetPosition()).Normalized();

    if (!reachedTarget)
    {
        //lerp position
        Vec2 actualPosition = MathUtils::Lerp(GetPosition(), targetPos, tick, m_speed);

        //set position on camera
        SetPosition(actualPosition);

        //update the camera
        Camera* cam = LogicManager::GetInstanceLogicManager()->GetCamera();
        cam->SetPostion(actualPosition + aimOffset * maxAimDistance);

        //position
        if (GetPosition().distance(targetPos) < 10.f)
        {
            reachedTarget = true;
        }
    }
    else
    {
        //position
        if (GetPosition().distance(targetPos) > 80.f)
        {
            reachedTarget = false;
        }

        //update the camera
        Camera* cam = LogicManager::GetInstanceLogicManager()->GetCamera();
        cam->SetPostion(GetPosition() + aimOffset * maxAimDistance);
    }
}

void GameCameraEntity::InputUpdate(InputManager* input_manager)
{
    Vec2 dir = input_manager->GetRightJoyStick().direction * input_manager->GetRightJoyStick().normalizedMagnitude;
    aimOffset = dir;
}
