#pragma once
#include "../GameUtils/MyEnums.h"

class Observer
{
public:
    virtual void OnNotify(ObserverEvents event);
};
