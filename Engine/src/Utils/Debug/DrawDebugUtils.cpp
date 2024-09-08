#include "DrawDebugUtils.h"

#include "DebugElem.h"
#include "../Camera.h"
#include "../../Engine_Managers/LogicManager.h"
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
