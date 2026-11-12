#pragma once
#include "Game.h"
#include "../../Entity.h"
#include "../../../Utils/StopWatch.h"
#include "../../../Utils/Text/Text.h"

class RegularGameManager : public Entity
{
    Game* m_Game = nullptr;

public:
    RegularGameManager();

    void BeginPlay() override;
    void RenderUpdate() override;
};
