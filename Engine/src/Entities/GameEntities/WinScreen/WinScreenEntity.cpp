#include "WinScreenEntity.h"
#include "../../../Engine_Managers/RenderEngine.h"
#include "../../../Engine_Managers/LogicManager.h"

WinScreenEntity::WinScreenEntity(const Vec2& position, int renderLayer): Entity(position, renderLayer)
{
    m_LoadingText = new Text("data/Fonts/pixelFont.ttf",
                             "Felicides, saliste del supermercado!!!", 30, Vec2(0.082f, 0.941f, 0.573f));
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    m_LoadingText->SetPosition(render_engine->GetScreenCenter() + Vec2(-280, 10));
}

WinScreenEntity::~WinScreenEntity()
{
    delete m_LoadingText;
    m_LoadingText = nullptr;
}

void WinScreenEntity::BeginPlay()
{
    m_stop_watch.Start();
    m_stop_watchLetters.Start();
}

void WinScreenEntity::LogicUpdate(double tick)
{
    m_stop_watch.ReceiveTick(tick);
    m_stop_watchLetters.ReceiveTick(tick);

    if (m_stop_watchLetters.GetElapsedMiliSeconds() > 100)
    {
        m_stop_watchLetters.ReStart();
        std::string aux = "Felicides, saliste del supermercado";
        numDots++;
        for (int i = 0; i < numDots % 6; ++i)
        {
            aux.append("!");
        }
        textLoading = aux;
    }


    if (m_stop_watch.GetElapsedSeconds() > m_waitTime)
    {
        LogicManager* logic_manager = LogicManager::GetInstanceLogicManager();

        //reset game
        logic_manager->GetSceneManager()->DeleteScene("GameLevel");
        logic_manager->GetSceneManager()->DeleteScene("Main_Menu");

        //load game
        logic_manager->SetCurrentScene(logic_manager->GetSceneManager()->GetMainMenu());
    }
}

void WinScreenEntity::RenderUpdate()
{
    // draw
    m_LoadingText->SetText(textLoading);

    m_LoadingText->Draw();
}
