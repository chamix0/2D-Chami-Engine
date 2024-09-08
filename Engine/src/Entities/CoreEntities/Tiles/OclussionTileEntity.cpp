#include "OclussionTileEntity.h"

#include "Enums.h"
#include "../../../Utils/Collision/Collider.h"
#include "../../../Utils/Sprite/Sprite.h"
#include "../../../Engine_Managers/LogicManager.h"
#include "../../../Utils/MathUtils.h"

OclussionTileEntity::OclussionTileEntity(Vec2 position, int renderLayer, std::string tag, std::string path, int numCols,
                                         int numRows,
                                         int id): TileEntity(position, renderLayer, tag, path, numCols, numRows, id)
{
    //create  sprite
    m_tileSprite = new Sprite(path, numCols, numRows, Vec2(1), BLEND_ALPHA,
                              Vec2(1), Vec2(0.5f), 0,
                              NONE, WORLD, id);

    //updata sprite
    m_tileSprite->update(0.f, position);

    //register sprite
    AddSprite(m_tileSprite);
}

void OclussionTileEntity::RenderUpdate()
{
    Entity::RenderUpdate();

    //draw sprite
    m_tileSprite->draw();
}

void OclussionTileEntity::BeginPlay()
{
    m_player = LogicManager::GetInstanceLogicManager()->GetCurrentScene()->GetPlayer();
}

void OclussionTileEntity::EarlyUpdate(double tick)
{
    updated = false;
    m_desiredAlpha = 1;
}

void OclussionTileEntity::LogicUpdate(double tick)
{
    float distance = m_player->GetPosition().distance(GetPosition());
    if (distance < m_detectionRange)
    {
        SetNeighborsAlpha();
    }
}

void OclussionTileEntity::LogicLateUpdate(double tick)
{
    //update alpha

    m_alpha = MathUtils::fLerp(m_alpha, m_desiredAlpha, tick, m_speed);
    m_tileSprite->setColor(Vec2(1, 1, 1, m_alpha));
}

void OclussionTileEntity::SetAlpha()
{
    updated = true;
    float distance = m_player->GetPosition().distance(GetPosition());
    m_desiredAlpha = MathUtils::NormalizeBetweenValues(distance, m_minDistance, m_maxDistance);
}

void OclussionTileEntity::SetNeighborsAlpha()
{
    //set self alpha
    SetAlpha();

    //propagate to neighbours
    for (TileEntity* tile : GetNeighBors())
    {
        OclussionTileEntity* ocTile = dynamic_cast<OclussionTileEntity*>(tile);
        if (ocTile != nullptr && !ocTile->updated)
        {
            ocTile->SetNeighborsAlpha();
        }
    }
}

bool OclussionTileEntity::GetUpdated() const
{
    return updated;
}
