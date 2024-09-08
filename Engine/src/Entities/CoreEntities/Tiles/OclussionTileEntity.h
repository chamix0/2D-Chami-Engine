#pragma once
#include "TileEntity.h"
#include "../../Entity.h"

class OclussionTileEntity : public TileEntity
{
private:
    Sprite* m_tileSprite = nullptr;
    Entity* m_player = nullptr;
    float m_alpha = 1;
    float m_desiredAlpha;
    float m_detectionRange = 32.f;
    float m_speed = 1.5f;

    float m_minDistance = 10.f;
    float m_maxDistance = 300.f;
    bool updated = false;

public:
    OclussionTileEntity(Vec2 position, int renderLayer, std::string tag, std::string path, int numCols, int numRows,
                        int id);
    void RenderUpdate() override;
    void BeginPlay() override;
    void LogicUpdate(double tick) override;
    void SetAlpha();
    void SetNeighborsAlpha();

    bool GetUpdated() const;
    void LogicLateUpdate(double tick) override;
    void EarlyUpdate(double tick) override;
};
