#include "MainMenuEntity.h"

#include "glfw3.h"
#include "../../../Engine_Managers/AudioManager.h"
#include "../../../Engine_Managers/LogicManager.h"
#include "../../../Engine_Managers/RenderEngine.h"
#include "../../../Scenes/SceneManager.h"
#include "../../../Utils/MathUtils.h"
#include "../../../Utils/GameUtils/GameSceneCreationUtils.h"
#include "../../../Utils/Sprite/Sprite.h"
#include "../../../Utils/UI/Button.h"
#include "../Dialogue/DialogueEntity.h"

void MainMenuEntity::CreateBackground()
{
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    //background
    std::vector<Sprite*> m_sprites;
    float tileSize = 32;
    float halfTileSize = tileSize / 2.f;
    int numSquaresWidth = render_engine->GetScreenWidth() / tileSize;
    int numSquaresHeight = render_engine->GetScreenHeight() / tileSize;

    Vec2 colorWhite = Vec2(1);
    Vec2 colorBlack = Vec2(43.f / 255.f, 47 / 255.f, 51 / 255.f);

    for (int x = 0; x < numSquaresWidth; ++x)
    {
        for (int y = 0; y < numSquaresHeight; ++y)
        {
            int color = x % 2 == 0 ? 1 : 0;
            color = y % 2 == 0 ? color : (color + 1) % 2;

            Sprite* BackgroundTile = new Sprite("data/Sprites/pixel.png", 1, 1,
                                                Vec2(color == 0 ? colorWhite : colorBlack), BLEND_SOLID,
                                                Vec2(tileSize), Vec2(0.5f, 0.5f), 0.f, CollisionType::NONE, UI);
            BackgroundTile->m_position = Vec2(tileSize * x + halfTileSize, tileSize * y + halfTileSize);
            AddSprite(BackgroundTile);
        }
    }
}

MainMenuEntity::MainMenuEntity(Vec2 position, int renderlayer) : Entity(position, renderlayer, "main_menu")
{
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    //background
    CreateBackground();

    //tittle text
    tittleText = new Text("data/Fonts/ChessTextFont.ttf", "A SIMPLE CHESS GAME", 60,
                          Vec2(1, 0.5, 0));
    tittleText->SetPosition(Vec2(render_engine->GetScreenCenter().x - 290, 205));

    Sprite* TitleBackground = new Sprite("data/Sprites/pixel.png", 1, 1,
                                         Vec2(1), BLEND_SOLID,
                                         Vec2(610, 70), Vec2(0.5f, 0.5f), 0.f, CollisionType::NONE, UI);
    TitleBackground->m_position = render_engine->GetScreenCenter() + Vec2(0, -215);
    AddSprite(TitleBackground);

    //buttons
    ButtonPlay = new Button("data/Game/UI/PlayButton.png", "data/Fonts/pixelFont.ttf", 32);
    ButtonPlay->SetText("Jugar");
    ButtonSettings = new Button("data/Game/UI/PlayButton.png", "data/Fonts/pixelFont.ttf", 32);
    ButtonSettings->SetText("Ajustes");
    ButtonCredits = new Button("data/Game/UI/PlayButton.png", "data/Fonts/pixelFont.ttf", 32);
    ButtonCredits->SetText("Creditos");
    ButtonExit = new Button("data/Game/UI/PlayButton.png", "data/Fonts/pixelFont.ttf", 32);
    ButtonExit->SetText("Salir");

    //add buttons to the array
    buttons.push_back(ButtonPlay);
    buttons.push_back(ButtonSettings);
    buttons.push_back(ButtonCredits);
    buttons.push_back(ButtonExit);

    //init pos
    Vec2 initialPos = render_engine->GetScreenCenter() + Vec2(0, 0);
    for (int i = 0; i < buttons.size(); ++i)
    {
        buttons[i]->SetPosition(initialPos + Vec2(0, 75) * i);
    }

    //bind on clicked events
    ButtonPlay->OnClicked_Event.Bind(this, &MainMenuEntity::OnPlayButtonPressed);
    ButtonSettings->OnClicked_Event.Bind(this, &MainMenuEntity::OnSettingsButtonPressed);
    ButtonCredits->OnClicked_Event.Bind(this, &MainMenuEntity::OnCreditsButtonPressed);
    ButtonExit->OnClicked_Event.Bind(this, &MainMenuEntity::OnExitButtonPressed);

    //audio sources
    backgroundSounds = AudioManager::GetInstanceAudioManager()->CreateAudioSource(
        1, 0.5f, true, RenderEngine::GetInstanceRenderEngine()->GetScreenCenter());
}

MainMenuEntity::~MainMenuEntity()
{
    //delete text
    delete tittleText;
    tittleText = nullptr;

    //delete buttons
    for (int i = 0; i < buttons.size(); ++i)
    {
        delete buttons[i];
        buttons[i] = nullptr;
    }
}

void MainMenuEntity::BeginPlay()
{
    //clean the game data
    LogicManager::GetInstanceLogicManager()->GetSceneManager()->DeleteAllScenes("Main_Menu");

    //highlight first button    
    SelectNone();

    //start playing sound
    // backgroundSounds->PlayClip("data/Audio/Music/SigmaChad.wav");
}

void MainMenuEntity::InputUpdate(InputManager* input_manager)
{
    //reset buttons highlight when mouse moved
    if (input_manager->GetMouseMovedThisFrame())
    {
        SelectNone();
    }

    //Buttons input update
    for (Button* button : buttons)
    {
        button->ProcessInputs(input_manager);
    }

    //inputs
    bool upInput = input_manager->CheckInstantInput(vk_Up) || input_manager->CheckInstantInput(vk_W) || input_manager->
        CheckInstantInputGamepad(GAMEPAD_DPAD_UP);
    bool downInput = input_manager->CheckInstantInput(vk_Down) || input_manager->CheckInstantInput(vk_S) ||
        input_manager->CheckInstantInputGamepad(GAMEPAD_DPAD_DOWN);
    bool acceptInput = input_manager->CheckInstantInput(vk_Space) ||
        input_manager->CheckInstantInputGamepad(GAMEPAD_SOUTH);

    //actions
    if (upInput)
    {
        SelectPrev();
    }
    else if (downInput)
    {
        SelectNext();
    }
    else if (acceptInput)
    {
        AcceptAction();
    }
}

void MainMenuEntity::RenderUpdate()
{
    for (Sprite* sprite : m_sprites)
    {
        sprite->draw();
    }

    //render background
    // BackgroundSprite->update(0, BackgroundSprite->m_position);
    // BackgroundSprite->draw();

    //render buttons
    for (Button* button : buttons)
    {
        button->Draw(button->GetPosition(), Vec2(20.f, 5));
    }

    //render text
    // tittleText->SetPosition(tittlePos);
    tittleText->Draw();
}

void MainMenuEntity::HiglightButton(int index)
{
    for (int i = 0; i < buttons.size(); ++i)
    {
        buttons[i]->SetSelected(i == index);
    }
}

void MainMenuEntity::SelectNone()
{
    buttonindex = -1;
    HiglightButton(-1);
}

void MainMenuEntity::SelectNext()
{
    buttonindex = MathUtils::Min(buttonindex + 1, buttons.size() - 1);
    HiglightButton(buttonindex);
    //play select sound
    AudioSource* instantSounds = AudioManager::GetInstanceAudioManager()->CreateAudioSource(
        1, 50, false, RenderEngine::GetInstanceRenderEngine()->GetScreenCenter());
    instantSounds->PlayClip("data/Audio/UI/Blip_Select.wav");
}

void MainMenuEntity::SelectPrev()
{
    buttonindex = MathUtils::Max(buttonindex - 1, 0);
    HiglightButton(buttonindex);
    //play select sound
    AudioSource* instantSounds = AudioManager::GetInstanceAudioManager()->CreateAudioSource(
        1, 50, false, RenderEngine::GetInstanceRenderEngine()->GetScreenCenter());
    instantSounds->PlayClip("data/Audio/UI/Blip_Select.wav");
}

void MainMenuEntity::AcceptAction()
{
    //play accept sound
    AudioSource* instantSounds = AudioManager::GetInstanceAudioManager()->CreateAudioSource(
        1, 50, false, RenderEngine::GetInstanceRenderEngine()->GetScreenCenter());
    instantSounds->PlayClip("data/Audio/UI/Accept.wav");

    //do button actions
    if (buttonindex == 0)
    {
        OnPlayButtonPressed();
    }
    else if (buttonindex == 1)
    {
        OnSettingsButtonPressed();
    }
    else if (buttonindex == 2)
    {
        OnCreditsButtonPressed();
    }
    else if (buttonindex == 3)
    {
        OnExitButtonPressed();
    }
}

void MainMenuEntity::OnPlayButtonPressed()
{
    SceneManager* scene_manager = LogicManager::GetInstanceLogicManager()->GetSceneManager();
    LogicManager::GetInstanceLogicManager()->SetCurrentScene(
        GameSceneCreationUtils::GetRegularGameLevel(*scene_manager));

    backgroundSounds->stop();
}

void MainMenuEntity::OnExitButtonPressed()
{
    LogicManager::GetInstanceLogicManager()->ExitAplication();
}

void MainMenuEntity::OnSettingsButtonPressed()
{
    DrawDebugUtils::AddToLog("Settings Button Pressed");
}

void MainMenuEntity::OnCreditsButtonPressed()
{
    DrawDebugUtils::AddToLog("Credits Button Pressed");
}

void MainMenuEntity::LogicUpdate(double tick)
{
    // RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    // aux += tick;
    // tittlePos = Vec2(render_engine->GetScreenCenter().x - 400,
    //                  75 + sinf(aux) * 15);
}
