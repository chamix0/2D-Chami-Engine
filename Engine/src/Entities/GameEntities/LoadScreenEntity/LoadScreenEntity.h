#pragma once
#include "../../Entity.h"
#include "../../../Utils/StopWatch.h"
#include "../../../Utils/Text/Text.h"

class LoadScreenEntity : public Entity
{
private:
    Text* m_LoadingText = nullptr;
    StopWatch m_stop_watch;
    StopWatch m_stop_watchLetters;
    float m_waitTime = 5;
    std::string textLoading="";
    int numDots=0;

public:
    LoadScreenEntity(const Vec2& position, int renderLayer);

    ~LoadScreenEntity() override;
    void BeginPlay() override;
    void LogicUpdate(double tick) override;
    void RenderUpdate() override;
    void Awake() override;
};
