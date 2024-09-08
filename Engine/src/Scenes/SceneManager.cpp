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



Scene* SceneManager::GetMainMenu()
{
    //doesnt exist
    if (scenes.find("Main_Menu") == scenes.end() || scenes["Main_Menu"] == nullptr)
    {
        //entity array
        std::map<int, std::vector<Entity*>> entities;

        //main menu entity
        MainMenuEntity* main_menu_entity = new MainMenuEntity(
            RenderEngine::GetInstanceRenderEngine()->GetScreenCenter(), 0);
        entities[main_menu_entity->GetRenderLayer()].push_back(main_menu_entity);
        Scene* scene = new Scene(entities);
        scenes["Main_Menu"] = scene;
        // scene->BeginPlay();
        return scene;
    }
    //exists
    return scenes["Main_Menu"];
}

Scene* SceneManager::GetGameLevel()
{
    //doesnt exist
    if (scenes.find("GameLevel") == scenes.end() || scenes["GameLevel"] == nullptr)
    {
        //entity array
        std::map<int, std::vector<Entity*>> entities;

        //camera
        GameCameraEntity* camera = new GameCameraEntity(
            RenderEngine::GetInstanceRenderEngine()->GetScreenCenter(),
            1);
        entities[camera->GetRenderLayer()].push_back(camera);

        //HUD
        HudEntity* hud = new HudEntity(RenderEngine::GetInstanceRenderEngine()->GetScreenCenter(),
            20);
        entities[hud->GetRenderLayer()].push_back(hud);

        //create scene
        Scene* scene = new Scene(entities);

        //load entities
        scene->LoadTileMap("data/Maps/Mercadona.tmx");
        scene->SetGameCameraEntity(camera);
        scenes["GameLevel"] = scene;

        return scene;
    }
    //exists
    return scenes["GameLevel"];
}

Scene* SceneManager::GetDialogueLevel(int mode, int dificulty)
{
    if (scenes.find("DialogueLevel") != scenes.end())
    {
        DeleteScene("DialogueLevel");
    }

    //entity array
    std::map<int, std::vector<Entity*>> entities;

    //dialogue entity
    DialogueEntity* dialogue_entity = new DialogueEntity(RenderEngine::GetInstanceRenderEngine()->GetScreenCenter(),
                                                         0);
    dialogue_entity->InitializeDialogue(static_cast<DialogueType>(mode), dificulty);


    entities[dialogue_entity->GetRenderLayer()].push_back(dialogue_entity);

    //create scene
    Scene* scene = new Scene(entities);
    scenes["DialogueLevel"] = scene;
    return scene;
}

Scene* SceneManager::LoadingGameLevel()
{
    //doesnt exist
    if (scenes.find("LoadGameLevel") == scenes.end() || scenes["LoadGameLevel"] == nullptr)
    {
        //entity array
        std::map<int, std::vector<Entity*>> entities;

        //screen
        LoadScreenEntity* loadScreen = new LoadScreenEntity(
            RenderEngine::GetInstanceRenderEngine()->GetScreenCenter(),
            1);
        entities[loadScreen->GetRenderLayer()].push_back(loadScreen);


        //create scene
        Scene* scene = new Scene(entities);
        scenes["LoadGameLevel"] = scene;
        return scene;
    }
    //exists
    return scenes["LoadGameLevel"];
}

Scene* SceneManager::GameOverLevel()
{
    //doesnt exist
    if (scenes.find("GameOver") == scenes.end() || scenes["GameOver"] == nullptr)
    {
        //entity array
        std::map<int, std::vector<Entity*>> entities;

        //screen
        GameOverScreenEntity* gamOverScreen = new GameOverScreenEntity(
            RenderEngine::GetInstanceRenderEngine()->GetScreenCenter(),
            1);
        entities[gamOverScreen->GetRenderLayer()].push_back(gamOverScreen);

        //create scene
        Scene* scene = new Scene(entities);

        scenes["GameOver"] = scene;
        return scene;
    }
    //exists
    return scenes["GameOver"];
}

Scene* SceneManager::GameWinLevel()
{
    //doesnt exist
    if (scenes.find("Win") == scenes.end() || scenes["Win"] == nullptr)
    {
        //entity array
        std::map<int, std::vector<Entity*>> entities;

        //screen
        WinScreenEntity* winScreen = new WinScreenEntity(
            RenderEngine::GetInstanceRenderEngine()->GetScreenCenter(),
            1);
        entities[winScreen->GetRenderLayer()].push_back(winScreen);

        //create scene
        Scene* scene = new Scene(entities);

        scenes["Win"] = scene;
        return scene;
    }

    //exists
    return scenes["Win"];
}




Scene* SceneManager::GetScene(std::string sceneName)
{
    //doesnt exist
    if (scenes.find(sceneName) == scenes.end())
    {
        return nullptr;
    }
    //exists
    return scenes[sceneName];
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
