#include "MainMenuEntity.h"

#include "glfw3.h"
#include "../../../Engine_Managers/AudioManager.h"
#include "../../../Engine_Managers/LogicManager.h"
#include "../../../Engine_Managers/RenderEngine.h"
#include "../../../Scenes/SceneManager.h"
#include "../../../Utils/MathUtils.h"
#include "../../../Utils/Sprite/Sprite.h"
#include "../../../Utils/UI/Button.h"
#include "../Dialogue/DialogueEntity.h"

MainMenuEntity::MainMenuEntity(Vec2 position, int renderlayer): Entity(position, renderlayer, "main_menu")
{
    //background
    BackgroundSprite = new Sprite("data/Game/UI/MainMenuBackground.png", 1, 1, Vec2(1), BLEND_SOLID,
                                  Vec2(8), Vec2(0.5f, 0.5f), 0.f, CollisionType::NONE, UI);
    AddSprite(BackgroundSprite);

    //tittle text
    tittleText = new Text("data/Fonts/Bubbleboddy.ttf", "The Average Shopping|Experience", 60,
                          Vec2(0));

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
    HiglightButton(buttonindex);
    //start playing sound
    backgroundSounds->PlayClip("data/Audio/Music/SigmaChad.wav");
}

void MainMenuEntity::InputUpdate(InputManager* input_manager)
{
    //inputs
    bool upInput = input_manager->CheckInstantInput(vk_Up) || input_manager->CheckInstantInput(vk_W) || input_manager->
        CheckInstantInput(GAMEPAD_DPAD_UP);
    bool downInput = input_manager->CheckInstantInput(vk_Down) || input_manager->CheckInstantInput(vk_S) ||
        input_manager->CheckInstantInput(GAMEPAD_DPAD_DOWN);
    bool acceptInput = input_manager->CheckInstantInput(vk_Space) ||
        input_manager->CheckInstantInput(GAMEPAD_SOUTH);

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
    //render background
    BackgroundSprite->update(0, m_position);
    BackgroundSprite->draw();

    //render buttons
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    Vec2 initialPos = Vec2(0, render_engine->GetScreenHeight()) + Vec2(100, -270);
    for (int i = 0; i < buttons.size(); ++i)
    {
        buttons[i]->Draw(initialPos + Vec2(0, 75) * i, Vec2(20.f, 5));
    }

    //render text
    tittleText->SetPosition(tittlePos);
    tittleText->Draw();
}

void MainMenuEntity::HiglightButton(int index)
{
    for (int i = 0; i < buttons.size(); ++i)
    {
        buttons[i]->SetSelected(i == index);
    }
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
        LogicManager::GetInstanceLogicManager()->SetCurrentScene(
            LogicManager::GetInstanceLogicManager()->GetSceneManager()->GetDialogueLevel(
                DialogueType::START_DIALOGUE, 0));

        // LogicManager::GetInstanceLogicManager()->SetCurrentScene(
        //     LogicManager::GetInstanceLogicManager()->GetSceneManager()->GetGameLevel());

        backgroundSounds->stop();
    }
    else if (buttonindex == 1)
    {
    }
    else if (buttonindex == 2)
    {
    }
    else if (buttonindex == 3)
    {
        LogicManager::GetInstanceLogicManager()->ExitAplication();
    }
}

void MainMenuEntity::LogicUpdate(double tick)
{
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    aux += tick;
    tittlePos = Vec2(render_engine->GetScreenCenter().x - 400,
                     75 + sinf(aux) * 15);
}
