#pragma once
#include "Dialogue.h"
#include "../../Entity.h"
#include "../../../Utils/StopWatch.h"

class Text;
class Sprite;

enum DialogueType
{
    START_DIALOGUE,
    ALIEN_DIALOGUE,
    CASHIER_DIALOGUE,
    DIALOGUE_COUNT
};

class DialogueEntity : public Entity
{
private:
    //background
    Sprite* m_BackgroundSprite = nullptr;
    Sprite* pannelSprite = nullptr;
    Sprite* m_pannelAnswersSprite = nullptr;
    Sprite* m_AlienSprite = nullptr;
    Sprite* m_timePanelSprite = nullptr;


    //current dialogue
    int dialogueIndex = 0;

    //tittle text
    Vec2 answersInitialPos;
    Text* m_DialogueText = nullptr;
    std::string m_dialogueBuffer;
    int dialogueLetterIndex = 0;
    Text* m_answerText = nullptr;

    std::string answerBuffer;
    int currentAnswerIndex = -1;
    StopWatch dialogueTextStopwatch;
    
    /*stopwatch*/
    // Alien  stop watch
    StopWatch m_stopWatch;
    float maxTime = 45.f;
    Text* m_timeText = nullptr;
    /*delete stopwatch*/
    StopWatch m_deleteStopWatch;
    int m_deleteCooldown = 100;
    float m_answerDesiredPos;
    float m_outPos;
    float m_showPos;

    //current dialogue
    Dialogue m_dialogue;
    DialogueType dialogueType;
    int m_difficulty = 0;

public:
    DialogueEntity(Vec2 position, int renderlayer);
    ~DialogueEntity() override;
    void InputUpdate(InputManager* input_manager) override;
    void RenderUpdate() override;
    void LogicUpdate(double tick) override;
    void InitializeDialogue(DialogueType type, int dificulty = 0);

private:
    Dialogue LoadDialogue(std::string path);
    void ShowCurrentDialogue();
    void NextDialogue();
    int ProcessAnswerInput(int index);
    int ProcessInput(InputManager* input_manager);
    void UpdateAnswer(int index, Vec2 offset = Vec2(0));

public:
    void BeginPlay() override;
    static bool strcmp2(char a, char b);
};
