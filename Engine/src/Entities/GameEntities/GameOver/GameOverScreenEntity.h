#pragma once
#include "../../Entity.h"
#include "../../../Utils/StopWatch.h"
#include "../../../Utils/Text/Text.h"


class GameOverScreenEntity : public Entity
{
private:
    Text* m_LoadingText = nullptr;
    StopWatch m_stop_watch;
    StopWatch m_stop_watchLetters;
    float m_waitTime = 5;
    std::string textLoading="";
    int numDots=0;

public:
    GameOverScreenEntity(const Vec2& position, int renderLayer);

    ~GameOverScreenEntity() override;
    void BeginPlay() override;
    void LogicUpdate(double tick) override;
    void RenderUpdate() override;
};
