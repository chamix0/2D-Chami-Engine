#include "GameOverScreenEntity.h"
#include "../../../Engine_Managers/LogicManager.h"
#include "../../../Engine_Managers/RenderEngine.h"
#include "../../../Utils/Sprite/Sprite.h"

GameOverScreenEntity::GameOverScreenEntity(const Vec2& position, int renderLayer): Entity(position, renderLayer)
{
    m_LoadingText = new Text("data/Fonts/pixelFont.ttf",
                             "GameOver...", 30, Vec2(0.431f, 0.376f, 0.259f));
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    m_LoadingText->SetPosition(render_engine->GetScreenCenter() + Vec2(-80, 10));
}

GameOverScreenEntity::~GameOverScreenEntity()
{
    delete m_LoadingText;
    m_LoadingText = nullptr;
}

void GameOverScreenEntity::BeginPlay()
{
    m_stop_watch.Start();
    m_stop_watchLetters.Start();
}

void GameOverScreenEntity::LogicUpdate(double tick)
{
    m_stop_watch.ReceiveTick(tick);
    m_stop_watchLetters.ReceiveTick(tick);

    if (m_stop_watchLetters.GetElapsedMiliSeconds() > 100)
    {
        m_stop_watchLetters.ReStart();
        std::string aux = "Game Over";
        numDots++;
        for (int i = 0; i < numDots % 4; ++i)
        {
            aux.append(".");
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

void GameOverScreenEntity::RenderUpdate()
{
    // draw
    m_LoadingText->SetText(textLoading);

    m_LoadingText->Draw();
}
