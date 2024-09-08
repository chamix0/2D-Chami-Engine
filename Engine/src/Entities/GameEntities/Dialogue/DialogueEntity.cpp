#include "DialogueEntity.h"

#include <algorithm>

#include "pugixml.hpp"
#include "../../../Engine_Managers/AudioManager.h"
#include "../../../Engine_Managers/LogicManager.h"
#include "../../../Engine_Managers/RenderEngine.h"
#include "../../../Utils/MathUtils.h"
#include "../../../Utils/Sprite/Sprite.h"
#include "../../../Utils/Text/Text.h"

DialogueEntity::DialogueEntity(Vec2 position, int renderlayer): Entity(position, renderlayer)
{
    //background
    m_BackgroundSprite = new Sprite("data/Game/UI/purpleTile.png", 1, 1, Vec2(1), BLEND_SOLID,
                                    Vec2(8), Vec2(0), 0.f, CollisionType::NONE, UI);
    AddSprite(m_BackgroundSprite);

    pannelSprite = new Sprite("data/Game/UI/SettingPannel.png", 2, 1, Vec2(1), BLEND_ALPHA, Vec2(4), Vec2(0.5f), 0,
                              NONE, UI, 1);

    //pannel sprite
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    pannelSprite->update(0, Vec2(render_engine->GetScreenWidth() / 2.f, 10));
    pannelSprite->m_angle = 90.f;

    AddSprite(pannelSprite);

    //answers pannel sprite
    m_pannelAnswersSprite = new Sprite("data/Game/UI/SettingPannel.png", 2, 1, Vec2(1), BLEND_ALPHA,
                                       Vec2(8.5, 7.5), Vec2(0.5f), 0, NONE, UI, 1);
    Vec2 answerPanelPos = Vec2(render_engine->GetScreenWidth() / 2.f,
                               render_engine->GetScreenHeight() + m_pannelAnswersSprite->size.y * m_pannelAnswersSprite
                               ->scale.y + 100);
    m_pannelAnswersSprite->update(0, answerPanelPos);
    AddSprite(m_pannelAnswersSprite);

    //alien sprite
    m_AlienSprite = new Sprite("data/ente.png", 1, 1, Vec2(1), BLEND_ALPHA,
                               Vec2(7), Vec2(0.5f), 0, NONE, UI, 1);;
    Vec2 entePos = Vec2(render_engine->GetScreenWidth() / 2.f + 800,
                        render_engine->GetScreenHeight() + m_AlienSprite->size.y * m_AlienSprite
                        ->scale.y + 100);
    m_AlienSprite->update(0, entePos);
    AddSprite(m_AlienSprite);

    //time panel
    m_timePanelSprite = new Sprite("data/panelTime.png", 1, 1, Vec2(1), BLEND_ALPHA,
                                   Vec2(0.3), Vec2(0), 0, NONE, UI, 1);
    m_timePanelSprite->update(0, Vec2(-5, -5));
    AddSprite(m_timePanelSprite);


    //dialogue text
    m_DialogueText = new Text("data/Fonts/pixelFont.ttf",
                              "", 25, Vec2(0.431f, 0.376f, 0.259f));

    //answer text
    m_answerText = new Text("data/Fonts/pixelFont.ttf",
                            "", 25, Vec2(0));

    //time text
    m_timeText = new Text("data/Fonts/pixelFont.ttf",
                          "", 30, Vec2(0.094f, 0.22f, 0.059f));
}

DialogueEntity::~DialogueEntity()
{
    delete m_DialogueText;
    m_DialogueText = nullptr;
    delete m_answerText;
    m_answerText = nullptr;
    delete m_timeText;
    m_timeText = nullptr;
}

void DialogueEntity::InputUpdate(InputManager* input_manager)
{
    //not reached options
    if (dialogueIndex < m_dialogue.m_texts.size() - 1)
    {
        bool nextInput = input_manager->CheckInstantInput(vk_Return) ||
            input_manager->CheckInstantInput(GAMEPAD_SOUTH);
        if (nextInput)
        {
            NextDialogue();
        }
    }
    else
    {
        //delete the las letter
        if (input_manager->CheckInstantInput(vk_BackSpace) || input_manager->CheckPressedInput(vk_BackSpace) &&
            m_deleteStopWatch.GetElapsedMiliSeconds() > static_cast<float>(m_deleteCooldown))
        {
            //reset timer
            m_deleteStopWatch.ReStart();

            if (answerBuffer.size() > 0)
            {
                //play key sound
                AudioManager::GetInstanceAudioManager()->PlayInstantSound("data/Audio/UI/keyTap.wav");

                //delete key
                answerBuffer.pop_back();
            }
        }
        //check the input text
        int result = ProcessInput(input_manager);

        //alien dialogue
        if (dialogueType == ALIEN_DIALOGUE)
        {
            if (result == -1) { return; }
            LogicManager* logic_manager = LogicManager::GetInstanceLogicManager();
            logic_manager->SetCurrentScene(logic_manager->GetSceneManager()->GetGameLevel());
            return;
        }


        //normal dialogue
        if (result == 0)
        {
            if (dialogueType == CASHIER_DIALOGUE)
            {
                LogicManager* logic_manager = LogicManager::GetInstanceLogicManager();
                logic_manager->SetCurrentScene(m_difficulty == -1
                                                   ? logic_manager->GetSceneManager()->GetGameLevel()
                                                   : logic_manager->GetSceneManager()->GameWinLevel());
            }
            else
            {
                LogicManager* logic_manager = LogicManager::GetInstanceLogicManager();
                logic_manager->SetCurrentScene(logic_manager->GetSceneManager()->LoadingGameLevel());
            }
        }
        else if (result == 1)
        {
            NextDialogue();
        }
    }
}

void DialogueEntity::RenderUpdate()
{
    //draw background
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    Vec2 size = m_BackgroundSprite->getSize() * m_BackgroundSprite->getScale();
    int numX = (render_engine->GetScreenWidth() / size.x) + 1;
    int numY = (render_engine->GetScreenHeight() / size.y) + 1;
    m_BackgroundSprite->setColor(dialogueType == ALIEN_DIALOGUE ? Vec2(1, 0, 0) : Vec2(1));
    for (int i = 0; i < numX; ++i)
    {
        for (int j = 0; j < numY; ++j)
        {
            m_BackgroundSprite->DrawScaled(Vec2(j * size.x, i * size.y), m_BackgroundSprite->getScale(), 1);
        }
    }
    //draw ente
    m_AlienSprite->setColor(dialogueType == ALIEN_DIALOGUE ? Vec2(1, 0, 0) : Vec2(0.137f, 0.447f, 0.69f));
    m_AlienSprite->draw();

    //draw pannel
    pannelSprite->draw();

    //draw answers
    m_pannelAnswersSprite->draw();

    //time
    if (dialogueType == ALIEN_DIALOGUE)
    {
        //panel
        m_timePanelSprite->draw();
        //set text
        m_timeText->SetPosition(Vec2(30, 70));
        m_timeText->SetSize(50);
        m_timeText->SetColor(Vec2(0.278, 0.4, 0.067));
        m_timeText->SetText(
            std::to_string(static_cast<int>((maxTime + maxTime * m_difficulty) - m_stopWatch.GetElapsedSeconds())));
        m_timeText->Draw();
    }

    m_timeText->SetPosition(Vec2(518, 200));
    m_timeText->SetColor(Vec2(0.412f, 0.251f, 0.f));
    m_timeText->SetSize(30);
    m_timeText->SetText(m_dialogue.m_name);
    m_timeText->Draw();

    //draw dialogue text
    ShowCurrentDialogue();
}

void DialogueEntity::LogicUpdate(double tick)
{
    //feed the stop watches
    m_stopWatch.ReceiveTick(tick);
    m_deleteStopWatch.ReceiveTick(tick);
    dialogueTextStopwatch.ReceiveTick(tick);


    //answer panel
    Vec2 answerPanelPos = Vec2(m_pannelAnswersSprite->m_position.x,
                               MathUtils::fLerp(m_pannelAnswersSprite->m_position.y, m_answerDesiredPos,
                                                tick, 5.f));
    m_pannelAnswersSprite->update(0, answerPanelPos);


    Vec2 entePos = MathUtils::Lerp(m_AlienSprite->m_position,
                                   RenderEngine::GetInstanceRenderEngine()->GetScreenCenter() + Vec2(0, -30), tick,
                                   5.f);

    m_AlienSprite->update(0, entePos);

    //when the ente is out end when time out
    if (dialogueType == ALIEN_DIALOGUE)
    {
        if (m_stopWatch.GetElapsedSeconds() > maxTime + maxTime * m_difficulty)
        {
            //load game over screen
            LogicManager::GetInstanceLogicManager()->SetCurrentScene(
                LogicManager::GetInstanceLogicManager()->GetSceneManager()->GameOverLevel());
        }
    }
}

void DialogueEntity::InitializeDialogue(DialogueType type, int dificulty)
{
    std::string dialogueAsset = "";
    int ranIndex = rand() % 4;
    switch (type)
    {
    case START_DIALOGUE:
        dialogueAsset = "data/Dialogues/startDialogue.xml";
        break;
    case ALIEN_DIALOGUE:
        if (ranIndex == 0)
        {
            dialogueAsset = "data/Dialogues/alien/pisoDialogue.xml";
        }
        else if (ranIndex == 1)
        {
            dialogueAsset = "data/Dialogues/alien/jefeDialogue.xml";
        }
        else if (ranIndex == 2)
        {
            dialogueAsset = "data/Dialogues/alien/profeDialogue.xml";
        }
        else if (ranIndex == 3)
        {
            dialogueAsset = "data/Dialogues/alien/exDialogue.xml";
        }
        else
        {
            dialogueAsset = "data/Dialogues/testDialogue.xml";
        }
        break;
    case CASHIER_DIALOGUE:
        if (dificulty == -1)
        {
            dialogueAsset = "data/Dialogues/cashierFail.xml";
        }
        else
        {
            dialogueAsset = "data/Dialogues/cashierSucced.xml";
        }
        break;
    case DIALOGUE_COUNT:
        dialogueAsset = "data/Dialogues/testDialogue.xml";
        break;
    }
    m_difficulty = dificulty;
    dialogueType = type;
    m_dialogue = LoadDialogue(dialogueAsset);
}

Dialogue DialogueEntity::LoadDialogue(std::string path)
{
    //xml document
    pugi::xml_document document;

    //when fails return an empty map
    if (!document.load_file(path.c_str())) return Dialogue();

    //get dialogue root node
    pugi::xml_node dialogueNode = document.child("Dialogue");

    //npc name
    std::string name = dialogueNode.attribute("name").as_string();

    //iterate texts
    std::vector<std::string> texts;
    for (pugi::xml_node textNode = dialogueNode.child("text"); textNode; textNode = textNode.
         next_sibling("text"))
    {
        std::string temp = textNode.attribute("text").as_string();
        texts.push_back(temp);
    }

    std::vector<std::string> options;
    for (pugi::xml_node optionNode = dialogueNode.child("option"); optionNode; optionNode = optionNode.
         next_sibling("option"))
    {
        std::string temp = optionNode.attribute("option").as_string();
        options.push_back(temp);
    }
    return Dialogue(name, texts, options);
}

void DialogueEntity::ShowCurrentDialogue()
{
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    //set text
    std::string dialogueTextToDisplay = "";
    for (int i = 0; i < MathUtils::Min(dialogueLetterIndex + 1, m_dialogue.m_texts[dialogueIndex].size()); ++i)
    {
        dialogueTextToDisplay += m_dialogue.m_texts[dialogueIndex][i];
    }

    Vec2 dialogueTextPos = Vec2(render_engine->GetScreenCenter().x - 210.f, 27.f);
    m_DialogueText->SetPosition(dialogueTextPos);
    m_DialogueText->SetText(dialogueTextToDisplay);
    m_DialogueText->Draw();
    m_answerDesiredPos = m_outPos;

    if (dialogueTextStopwatch.GetElapsedMiliSeconds() > 50)
    {
        dialogueTextStopwatch.ReStart();
        dialogueLetterIndex++;
    }


    //set options if its last index
    if (dialogueIndex == m_dialogue.m_texts.size() - 1)
    {
        //move the panel up
        m_answerDesiredPos = m_showPos;

        //enemy dialogue
        if (dialogueType == ALIEN_DIALOGUE)
        {
            UpdateAnswer(m_difficulty);
            return;
        }

        //normal dialogue
        //set options
        for (int i = 0; i < m_dialogue.m_options.size(); ++i)
        {
            UpdateAnswer(i, Vec2(0, i * 50));
        }
    }
}


void DialogueEntity::NextDialogue()
{
    if (dialogueLetterIndex < m_dialogue.m_texts[dialogueIndex].size() - 1)
    {
        dialogueLetterIndex = m_dialogue.m_texts[dialogueIndex].size() - 1;
        dialogueTextStopwatch.ReStart();
        return;
    }
    //play talk sound
    dialogueType == ALIEN_DIALOGUE
        ? AudioManager::GetInstanceAudioManager()->PlayInstantSound("data/Audio/talkBad.wav")
        : AudioManager::GetInstanceAudioManager()->PlayInstantSound("data/Audio/talk.wav");

    //clean the answer buffer
    answerBuffer = "";

    //go to the next dialog
    dialogueIndex = (dialogueIndex + 1) % m_dialogue.m_texts.size();
    dialogueLetterIndex = 0;
}

int DialogueEntity::ProcessAnswerInput(int index)
{
    int answerIndex = -1;
    //get current text
    std::string currentText = m_dialogue.m_options[index];

    //compare each letter
    for (int j = 0; j < answerBuffer.length(); ++j)
    {
        //current letter
        char aux = currentText[j];

        //is different
        if (!strcmp2(answerBuffer[j], aux))
        {
            //jump to the next line character
            if (currentText[j] == '|')
            {
                answerBuffer.pop_back();
                answerBuffer += '|';
                // currentAnswerIndex = -1;
                return index;
            }

            //if its the first letter its not found other wise it is
            answerIndex = j == 0 ? -1 : index;
            if (answerIndex != -1)
            {
                //remove the incorrect letter and return the answer index
                if (answerBuffer.size() > 0)
                {
                    answerBuffer.pop_back();
                }
                return index;
            }

            //if not found then try the next answer
            break;
        }

        answerIndex = index;
    }

    return answerIndex;
}

int DialogueEntity::ProcessInput(InputManager* input_manager)
{
    std::string currentLetter = input_manager->GetCurrentAbcKey();

    if (currentLetter == "")
    {
        return -1;
    }

    //play key sound
    AudioManager::GetInstanceAudioManager()->PlayInstantSound("data/Audio/UI/keyTap.wav");

    if (answerBuffer.size() > 0 && answerBuffer[answerBuffer.length() - 1] == ' ' && currentLetter[0] == ' ')
    {
        return -1;
    }

    std::string targetText = dialogueType == ALIEN_DIALOGUE ? m_dialogue.m_options[m_difficulty] : "";
    currentAnswerIndex = dialogueType == ALIEN_DIALOGUE ? m_difficulty : -1;

    //get first letter if empty
    answerBuffer.append(currentLetter);

    //on alien dialogue there is only one answer (difficulty index)
    if (dialogueType == ALIEN_DIALOGUE)
    {
        currentAnswerIndex = ProcessAnswerInput(m_difficulty);
        targetText = m_dialogue.m_options[m_difficulty];
    }

    //find which one is the one we are writting
    else
    {
        for (int i = 0; i < m_dialogue.m_options.size(); ++i)
        {
            //get current index
            currentAnswerIndex = ProcessAnswerInput(i);

            //there is a current index so set the text target
            if (currentAnswerIndex != -1)
            {
                targetText = m_dialogue.m_options[currentAnswerIndex];
                break;
            }
        }
    }

    //exit if no target text
    if (currentAnswerIndex == -1)
    {
        //remove the incorrect letter and return the answer index
        if (answerBuffer.size() > 0)
        {
            answerBuffer.pop_back();
        }
        return -1;
    }

    //if completed exit
    if (answerBuffer.length() >= targetText.length())
    {
        return currentAnswerIndex;
    }
    return -1;
}

void DialogueEntity::UpdateAnswer(int index, Vec2 offset)
{
    std::string aux = "- ";
    aux.append(m_dialogue.m_options[index]);
    std::transform(aux.begin(), aux.end(), aux.begin(), ::toupper);

    m_answerText->SetPosition(m_pannelAnswersSprite->m_position + Vec2(-390, -405) + offset);
    m_answerText->SetColor(Vec2(0));

    m_answerText->SetText(aux);
    m_answerText->Draw();

    //draw buffer
    if (currentAnswerIndex == index)
    {
        std::string buff = answerBuffer;

        //hint text
        std::string aux1 = "- ";
        char nextChar = m_dialogue.m_options[index][answerBuffer.size()];
        aux1.append(buff += nextChar == ' ' ? '_' : nextChar);
        std::transform(aux1.begin(), aux1.end(), aux1.begin(), ::toupper);

        m_answerText->SetColor(Vec2(0.5f));
        m_answerText->SetText(aux1);
        m_answerText->Draw();

        //actual text
        std::string aux2 = "- ";
        aux2.append(answerBuffer);
        std::transform(aux2.begin(), aux2.end(), aux2.begin(), ::toupper);

        m_answerText->SetColor(Vec2(1));
        m_answerText->SetText(aux2);
        m_answerText->Draw();
    }
}

void DialogueEntity::BeginPlay()
{
    dialogueType == ALIEN_DIALOGUE
        ? AudioManager::GetInstanceAudioManager()->PlayInstantSound("data/Audio/talkBad.wav")
        : AudioManager::GetInstanceAudioManager()->PlayInstantSound("data/Audio/talk.wav");


    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    answersInitialPos = Vec2(10, render_engine->GetScreenHeight() - 200);
    //set answer positions
    m_showPos = RenderEngine::GetInstanceRenderEngine()->GetScreenHeight() + 190;
    m_outPos = 1250;
    m_answerDesiredPos = m_outPos;

    //start  stop watches
    m_stopWatch.Start();
    m_deleteStopWatch.Start();
    dialogueTextStopwatch.Start();
}

bool DialogueEntity::strcmp2(char a, char b)
{
    if (toupper(a) != toupper(b)) return false;

    return true;
}
