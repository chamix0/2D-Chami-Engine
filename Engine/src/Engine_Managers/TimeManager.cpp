#include "TimeManager.h"

#include <glfw3.h>

TimeManager::TimeManager(double iTimeScale) : timeScale(iTimeScale)
{
    prevTime = GetTime();
}

void TimeManager::InitSlotsToProcess()
{
    currentTime = GetTime();
    //add the elapsed time since the last game logic update
    double elapsed = (currentTime - prevTime);

    totalTime += elapsed;
    FPS = 1 / elapsed;
    deltaTime += elapsed;

    //update previous time 
    prevTime = currentTime;

    // to fix the dead loop
    if (deltaTime >= deadLoopTick)
    {
        deltaTime = deadLoopTick;
    }
}

bool TimeManager::ProcessSlots()
{
    if (deltaTime >= fixedTick)
    {
        //subtract fixed tick from elapsed
        deltaTime -= fixedTick;
        return true;
    }
    return false;
}

double TimeManager::LogicWorldSlot()
{
    logicTime += fixedTick * timeScale;
    return fixedTick * timeScale;
}

double TimeManager::GetFixedTick() const
{
    return fixedTick;
}

double TimeManager::GetTotalTime() const
{
    return totalTime;
}

double TimeManager::GetLogicTime() const
{
    return logicTime;
}

double TimeManager::GetFps() const
{
    return FPS;
}

double TimeManager::GetTimeScale() const
{
    return timeScale;
}

void TimeManager::SetTimeScale(double value)
{
    timeScale = value;
}

double TimeManager::GetTime()
{
    return glfwGetTime();
}
