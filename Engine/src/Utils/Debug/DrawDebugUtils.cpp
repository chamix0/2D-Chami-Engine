#include "DrawDebugUtils.h"

#include "DebugElem.h"
#include "../Camera.h"
#include "../../Engine_Managers/LogicManager.h"
#include "../GameUtils/DEFINES_ENGINE.h"

#include "../../Engine_Managers/RenderEngine.h"

void DrawDebugUtils::DrawDebugPoint(Vec2 pos, Vec2 color)
{
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    Vec2 position = LogicManager::GetInstanceLogicManager()->GetCamera()->WorldPosToScreen(pos);
    render_engine->AddDebug(DebugElem(DebugType_POINT, position, Vec2(), Vec2(), Vec2(), color));
}

void DrawDebugUtils::DrawDebugSquare(Vec2 pos, Vec2 offset, float size, Vec2 color)
{
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    Vec2 position = LogicManager::GetInstanceLogicManager()->GetCamera()->WorldPosToScreen(pos);
    render_engine->AddDebug(DebugElem(DebugType_SQUARE, position, offset, Vec2(size, size), Vec2(), color));
}

void DrawDebugUtils::DrawDebugRect(Vec2 pos, Vec2 offset, Vec2 size, Vec2 color)
{
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    Vec2 position = LogicManager::GetInstanceLogicManager()->GetCamera()->WorldPosToScreen(pos);

    render_engine->AddDebug(DebugElem(DebugType_RECTANGLE, position, offset, size, Vec2(), color));
}

void DrawDebugUtils::DrawDebugLine(Vec2 start, Vec2 end, Vec2 color)
{
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    Vec2 position1 = LogicManager::GetInstanceLogicManager()->GetCamera()->WorldPosToScreen(start);
    Vec2 position2 = LogicManager::GetInstanceLogicManager()->GetCamera()->WorldPosToScreen(end);

    render_engine->AddDebug(DebugElem(DebugType_LINE, position1, Vec2(), Vec2(), position2, color));
}

void DrawDebugUtils::DrawDebugCircle(Vec2 pos, float radius, Vec2 color)
{
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    Vec2 position = LogicManager::GetInstanceLogicManager()->GetCamera()->WorldPosToScreen(pos - Vec2(radius, radius));
    render_engine->AddDebug(DebugElem(DebugType_CIRCLE, position, Vec2(),
                                      Vec2(radius * 2, radius * 2),
                                      Vec2(), color));
}

void DrawDebugUtils::DrawDebugOval(Vec2 pos, Vec2 size, Vec2 color)
{
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    Vec2 position = LogicManager::GetInstanceLogicManager()->GetCamera()->WorldPosToScreen(pos - size);
    render_engine->AddDebug(DebugElem(DebugType_OVAL, position, Vec2(), size * 2, Vec2(), color));
}

int DrawDebugUtils::AddToLog(std::string text)
{
#ifdef ADD_LOGS
    FILE* archivo = fopen("LOG.txt", "a");

    if (archivo == NULL)
    {
        printf("File could not be opened.\n");
        return 1;
    }

    //add text to log with a time stamp at the start
    fprintf(archivo, "%s %s \n", GetCurrentDateTimeStamp().c_str(), text.c_str());

    fclose(archivo);
#endif

    return 0;
}

int DrawDebugUtils::ClearLog()
{
    FILE* archivo = fopen("LOG.txt", "w");

    if (archivo == NULL)
    {
        printf("File could not be opened.\n");
        return 1;
    }

    fprintf(archivo, "");

    fclose(archivo);
    return 0;
}

std::string DrawDebugUtils::GetCurrentDateTimeStamp()
{
    time_t timestamp = time(&timestamp);
    return GetTimeToStamp(timestamp);
}

time_t DrawDebugUtils::GetCurrentRealTime()
{
    return time(NULL);
}

std::string DrawDebugUtils::GetTimeToStamp(time_t time)
{
    tm datetime = *localtime(&time);

    std::string text = "[" + std::to_string(datetime.tm_mday) + "/" + std::to_string(datetime.tm_mon + 1) + "/" +
        std::to_string(
            datetime.tm_year + 1900) + " " + std::to_string(datetime.tm_hour) + ":" + std::to_string(datetime.tm_min) +
        "." + std::to_string(datetime.tm_sec) + "]";
    return text;
}
