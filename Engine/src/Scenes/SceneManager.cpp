#include "SceneManager.h"

#include "../Engine_Managers/LogicManager.h"
#include "../Engine_Managers/RenderEngine.h"
#include "../Entities/GameEntities/Camera/GameCameraEntity.h"
#include "../Entities/GameEntities/Dialogue/DialogueEntity.h"
#include "../Entities/GameEntities/GameOver/GameOverScreenEntity.h"
#include "../Entities/GameEntities/LoadScreenEntity/LoadScreenEntity.h"
#include "../Entities/GameEntities/MainMenu/MainMenuEntity.h"
#include "../Entities/GameEntities/Player/Hud/HudEntity.h"
#include "../Entities/GameEntities/WinScreen/WinScreenEntity.h"
#include "../Utils/Debug/DrawDebugUtils.h"




Scene* SceneManager::GetScene(std::string sceneName)
{
    //doesnt exist
    if (scenes.find(sceneName) == scenes.end())
    {
        DrawDebugUtils::AddToLog("Scene ["+ sceneName+"] not found.");
        return nullptr;
    }
    
    //exists
    return scenes[sceneName];
}

void SceneManager::AddScene(std::string sceneName, Scene* scene)
{
    if (scene != nullptr)
    {
        scenes[sceneName] = scene;
    }
    
    DrawDebugUtils::AddToLog("Scene ["+ sceneName+"] could not be added.");
}


void SceneManager::DeleteScene(std::string scene)
{
    delete scenes[scene];
    scenes[scene] = nullptr;
}

void SceneManager::DeleteAllScenes()
{
    //delete all the scenes
    std::map<std::string, Scene*> aux = scenes;

    for (auto& kv : aux)
    {
        DeleteScene(kv.first);
    }
}

void SceneManager::DeleteAllScenes(std::string scene)
{
    //delete all the scenes
    std::map<std::string, Scene*> aux = scenes;

    for (auto& kv : aux)
    {
        if (kv.first != scene)
        {
            DeleteScene(kv.first);
        }
    }
    //empty map
    // scenes.clear();
}
