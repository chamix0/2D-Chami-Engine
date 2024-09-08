#pragma once
#include "TileEntity.h"
#include "../../../Utils/StopWatch.h"
#include "../../../Utils/Audio/AudioSource.h"
#include "../../GameEntities/Player/PlayerEntity.h"

class AlienTileEntity : public TileEntity
{
private:
    Sprite* m_tileSprite = nullptr;
    PlayerEntity* m_player = nullptr;
    AudioSource* audio_source = nullptr;
    float m_alpha = 1;
    float m_desiredAlpha;
    float m_detectionRange = 550.f;
    float m_speed = 1.5f;

    float m_minDistance = 64.f;
    float m_maxDistance = 350.f;
    bool updated = false;
    bool hasAlien = false;

    StopWatch stop_watch;
    StopWatch m_killStopwatch;
    float killCooldown = 10.f;
    float cooldown = 1.f;
    float maxCooldown = 1.f;

    int maxDepth = 3;

public:
    AlienTileEntity(Vec2 position, int renderLayer, std::string tag, std::string path, int numCols, int numRows,
                    int id);
    void RenderUpdate() override;
    void BeginPlay() override;
    void LogicUpdate(double tick) override;
    void SetAlpha(Vec2 position);
    void SetNeighborsAlpha(Vec2 position, int depth);
    void Move();
    bool GetUpdated() const;
    void LogicLateUpdate(double tick) override;
    void EarlyUpdate(double tick) override;
    void SetHasAlien(bool value);

    void changeAlienLocation(int depth = 0);
    int GetDifficulty();
    void UpdateDifficulty();


};
