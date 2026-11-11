#pragma once
#include "../../Entity.h"

class AudioSource;
class Text;
//forward declaration
class Sprite;
class Button;

class MainMenuEntity : public Entity
{
private:
    //background
    // Sprite* BackgroundSprite = nullptr;

    //buttons
    Button* ButtonPlay = nullptr;
    Button* ButtonSettings = nullptr;
    Button* ButtonCredits = nullptr;
    Button* ButtonExit = nullptr;
    std::vector<Button*> buttons;
    int buttonindex = 0;

    //tittle text
    Text* tittleText = nullptr;
    // Vec2 tittlePos;
    float aux = 0;

    //audio sources
    // AudioSource* instantSounds = nullptr;
    AudioSource* backgroundSounds = nullptr;

public:
    void CreateBackground();
    MainMenuEntity(Vec2 position, int renderlayer);
    ~MainMenuEntity();
    void BeginPlay() override;
    void InputUpdate(InputManager* input_manager) override;
    void RenderUpdate() override;
    void HiglightButton(int index);
    void SelectNone();
    void SelectNext();
    void SelectPrev();
    void AcceptAction();

    //events
    void OnPlayButtonPressed();
    void OnExitButtonPressed();
    void OnSettingsButtonPressed();
    void OnCreditsButtonPressed();


    void LogicUpdate(double tick) override;
};
