#include "LogicManager.h"

#include "glfw3.h"
#include "RenderEngine.h"
#include "TimeManager.h"
#include "../Entities/CoreEntities/SquareEntity.h"
#include "../Entities/CoreEntities/FontEntity.h"


LogicManager* LogicManager::logicInstance = nullptr;


LogicManager* LogicManager::GetInstanceLogicManager()
{
    if (logicInstance == nullptr)
    {
        logicInstance = new LogicManager();
    }
    return logicInstance;
}


void LogicManager::Init()
{
    //prueba de inputs
    // currentScene = sceneManager.LoadInputsScene();

    //practica 1
    // currentScene = sceneManager.LoadP1Scene();

    //practica 2
    // currentScene = sceneManager.LoadP2Scene();

    //practica 3
    // currentScene = sceneManager.LoadP3Scene();

    //practica 4
    // currentScene = sceneManager.LoadP4Scene();

    //practica 5
    // currentScene = sceneManager.LoadP5Scene();

    //practica 6
    // currentScene = sceneManager.LoadP6Scene();

    //practica 7
    // currentScene = sceneManager.GetP7Scene();

    //main menu
    SetCurrentScene(sceneManager.GetMainMenu());
}

void LogicManager::UpdateInputs(InputManager* input_manager)
{
    //get the inputs from the OS
    input_manager->UpdateInputs();

    //send the inputs to the enities
    for (auto& kv : currentScene->GetEntities())
    {
        for (size_t i = 0; i < kv.second.size(); i++)
        {
            kv.second[i]->InputUpdate(input_manager);
        }
    }
}

void LogicManager::UpdateCollisions(Entity* entity)
{
    std::vector<Entity*> entities = GetEntitiesArray();

    for (size_t i = 0; i < entities.size(); i++)
    {
        Entity* otherEntity = entities[i];

        if (otherEntity == entity || !otherEntity->HasCollision())
        {
            continue;
        }


        bool collides = entity->Collides(otherEntity);

        if (collides)
        {
            //it was not colliding before so trigger on collision enter
            if (!entity->GetColliding(otherEntity))
            {
                //set colliding with j entity
                entity->SetColliding(otherEntity, true);

                //trigger collision envent
                entity->OnCollisionEnter(otherEntity);
            }
            //it was  colliding before so trigger on collision stay
            else
            {
                //trigger event
                entity->OnCollisionStay(otherEntity);
            }
        }
        else
        {
            //it was colliding before but not any more so trigger on collision exit
            if (entity->GetColliding(otherEntity))
            {
                //set to not colliding
                entity->SetColliding(otherEntity, false);

                //trigger event
                entity->OnCollisionExit(otherEntity);
            }
        }
    }
}


void LogicManager::UpdateGameLogic(TimeManager& timer)
{
    //set the timer
    if (timeManager == nullptr)
    {
        timeManager = &timer;
    }

    //init slots
    timeManager->InitSlotsToProcess();

    //delete marked entities
    currentScene->RemoveMarkedEntities();

    while (timeManager->ProcessSlots())
    {
        //logic time and tick in game
        double logicTick = timeManager->LogicWorldSlot();

        //Early update
        for (auto& kv : currentScene->GetEntities())
        {
            for (size_t i = 0; i < kv.second.size(); i++)
            {
                kv.second[i]->EarlyUpdate(logicTick);
            }
        }

        //update
        for (auto& kv : currentScene->GetEntities())
        {
            for (size_t i = 0; i < kv.second.size(); i++)
            {
                kv.second[i]->LogicUpdate(logicTick);
            }
        }

        //late update 
        for (auto& kv : currentScene->GetEntities())
        {
            for (size_t i = 0; i < kv.second.size(); i++)
            {
                kv.second[i]->LogicLateUpdate(logicTick);
            }
        }
    }

    //update camera position
    GetCamera()->UpdateCamera();
}

void LogicManager::ShutDown()
{
    //delete all the entities
    sceneManager.DeleteAllScenes();
}


void LogicManager::SetPause(bool pause)
{
    if (timeManager != nullptr)
    {
        //stop time 
        if (pause)
        {
            timeManager->SetTimeScale(0);
        }
        //continue time
        else
        {
            timeManager->SetTimeScale(1);
        }
    }
}

bool LogicManager::GetPaused()
{
    return timeManager->GetTimeScale() == 0;
}

std::map<int, std::vector<Entity*>> LogicManager::GetEntities()
{
    return currentScene->GetEntities();
}

std::vector<Entity*> LogicManager::GetEntitiesArray()
{
    return currentScene->GetEntitiesArray();
}

Camera* LogicManager::GetCamera()
{
    return currentScene->GetCamera();
}

std::vector<Entity*> LogicManager::FindEntitiesWithTag(std::string tag)
{
    //auxiliar vector to return the entities
    std::vector<Entity*> foundEntities;

    //iterate all entities and check if they have that tag
    for (Entity* elem : GetEntitiesArray())
    {
        if (elem->GetTag() == tag)
        {
            foundEntities.push_back(elem);
        }
    }
    return foundEntities;
}

void LogicManager::ExitAplication()
{
    //window reference
    GLFWwindow* window = glfwGetCurrentContext();

    //close the window
    glfwSetWindowShouldClose(window, 1);
}


TimeManager* LogicManager::GetTimeManager() const
{
    return timeManager;
}


SceneManager* LogicManager::GetSceneManager()
{
    return &sceneManager;
}

void LogicManager::SetCurrentScene(Scene* scene)
{
    currentScene = scene;
    if (!currentScene->GetLoaded())
    {
        currentScene->InitScene();
    }
}

Scene* LogicManager::GetCurrentScene() const
{
    return currentScene;
}
