#include "LoadScreenEntity.h"

#include "../../../Engine_Managers/LogicManager.h"
#include "../../../Engine_Managers/RenderEngine.h"
#include "../../../Utils/Sprite/Sprite.h"

LoadScreenEntity::LoadScreenEntity(const Vec2& position, int renderLayer): Entity(position, renderLayer)
{
    m_LoadingText = new Text("data/Fonts/pixelFont.ttf",
                             "Cargando...", 30, Vec2(0.431f, 0.376f, 0.259f));
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    m_LoadingText->SetPosition(render_engine->GetScreenCenter()+Vec2(-80,10));
}

LoadScreenEntity::~LoadScreenEntity()
{
    delete m_LoadingText;
    m_LoadingText = nullptr;
}

void LoadScreenEntity::BeginPlay()
{
    m_stop_watch.Start();
    m_stop_watchLetters.Start();
}

void LoadScreenEntity::LogicUpdate(double tick)
{
    m_stop_watch.ReceiveTick(tick);
    m_stop_watchLetters.ReceiveTick(tick);

    if (m_stop_watchLetters.GetElapsedMiliSeconds() > 100)
    {
        m_stop_watchLetters.ReStart();
        std::string aux = "Cargando";
        numDots++;
        for (int i = 0; i < numDots % 4; ++i)
        {
            aux.append(".");
        }
        textLoading = aux;
    }


    if (m_stop_watch.GetElapsedSeconds() > m_waitTime)
    {
        //load game
        LogicManager* logic_manager = LogicManager::GetInstanceLogicManager();
        logic_manager->SetCurrentScene(logic_manager->GetSceneManager()->GetGameLevel());
    }
}

void LoadScreenEntity::RenderUpdate()
{
    // draw
    m_LoadingText->SetText(textLoading);

    m_LoadingText->Draw();
}

void LoadScreenEntity::Awake()
{
    Entity::Awake();
}
