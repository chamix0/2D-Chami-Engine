#pragma once
#include "../../Entity.h"
#include "../../../Utils/StopWatch.h"
#include "../../../Utils/Text/Text.h"

class RegularGameManager : public Entity
{
public:
     RegularGameManager();
    
    void BeginPlay() override;
    
    void RenderUpdate() override;
};
