#include "../src/Scenes/SceneManager.h"
#include "../src/Entities/GameEntities/MainMenu/MainMenuEntity.h"
#include "../src/Entities/GameEntities/Player/Hud/HudEntity.h"
#include "../src/Entities/GameEntities/Dialogue/DialogueEntity.h"
#include "../src/Entities/GameEntities/GameOver/GameOverScreenEntity.h"
#include "../src/Entities/GameEntities/WinScreen/WinScreenEntity.h"
#include "../src/Entities/GameEntities/LoadScreenEntity/LoadScreenEntity.h"
#include "../src/Entities/GameEntities/RegularGame/RegularGameManager.h"
#include "../src/Engine_Managers/RenderEngine.h"
#include "GameSceneCreationUtils.h"

Scene* GameSceneCreationUtils::GetMainMenu(SceneManager& sceneManager)
{
    Scene* scene = sceneManager.GetScene("Main_Menu");
    //doesnt exist
    if (scene == nullptr)
    {
        //entity array
        std::map<int, std::vector<Entity*>> entities;

        //main menu entity
        MainMenuEntity* main_menu_entity = new MainMenuEntity(
            RenderEngine::GetInstanceRenderEngine()->GetScreenCenter(), 0);
        entities[main_menu_entity->GetRenderLayer()].push_back(main_menu_entity);

        //create scene
        scene = new Scene(entities);
        sceneManager.AddScene("Main_Menu", scene);

        return scene;
    }

    //exists
    return scene;
}

Scene* GameSceneCreationUtils::GetRegularGameLevel(SceneManager& sceneManager)
{
    std::string sceneName="RegularGameLevel";
    Scene* scene = sceneManager.GetScene(sceneName);

    //doesnt exist
    if (scene == nullptr)
    {
        //entity array
        std::map<int, std::vector<Entity*>> entities;
        
        //Game manager entity
        RegularGameManager* regularGameManager = new RegularGameManager();
        entities[regularGameManager->GetRenderLayer()].push_back(regularGameManager);


        //camera
        GameCameraEntity* camera = new GameCameraEntity(
            RenderEngine::GetInstanceRenderEngine()->GetScreenCenter(),
            1);
        entities[camera->GetRenderLayer()].push_back(camera);

        //HUD
        // HudEntity* hud = new HudEntity(RenderEngine::GetInstanceRenderEngine()->GetScreenCenter(),
        //                                20);
        // entities[hud->GetRenderLayer()].push_back(hud);

        //create scene
        scene = new Scene(entities);

        //load entities
        // scene->LoadTileMap("data/Maps/Mercadona.tmx");
        scene->SetGameCameraEntity(camera);
        sceneManager.AddScene(sceneName, scene);

        return scene;
    }
    
    //exists
    return scene;   
}

Scene* GameSceneCreationUtils::GetGameLevel(SceneManager& sceneManager)
{
    Scene* scene = sceneManager.GetScene("GameLevel");

    //doesnt exist
    if (scene == nullptr)
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
        scene = new Scene(entities);

        //load entities
        scene->LoadTileMap("data/Maps/Mercadona.tmx");
        scene->SetGameCameraEntity(camera);
        sceneManager.AddScene("GameLevel", scene);

        return scene;
    }
    //exists
    return scene;
}

Scene* GameSceneCreationUtils::GetDialogueLevel(SceneManager& sceneManager, int mode, int dificulty)
{
    Scene* scene = sceneManager.GetScene("DialogueLevel");

    if (scene != nullptr)
    {
        sceneManager.DeleteScene("DialogueLevel");
    }

    //entity array
    std::map<int, std::vector<Entity*>> entities;

    //dialogue entity
    DialogueEntity* dialogue_entity = new DialogueEntity(RenderEngine::GetInstanceRenderEngine()->GetScreenCenter(),
                                                         0);
    dialogue_entity->InitializeDialogue(static_cast<DialogueType>(mode), dificulty);


    entities[dialogue_entity->GetRenderLayer()].push_back(dialogue_entity);

    //create scene
    scene = new Scene(entities);
    sceneManager.AddScene("DialogueLevel", scene);
    return scene;
}

Scene* GameSceneCreationUtils::LoadingGameLevel(SceneManager& sceneManager)
{
    Scene* scene = sceneManager.GetScene("LoadingGameLevel");
    //doesnt exist
    if (scene == nullptr)
    {
        //entity array
        std::map<int, std::vector<Entity*>> entities;

        //screen
        LoadScreenEntity* loadScreen = new LoadScreenEntity(
            RenderEngine::GetInstanceRenderEngine()->GetScreenCenter(),
            1);
        entities[loadScreen->GetRenderLayer()].push_back(loadScreen);


        //create scene
        scene = new Scene(entities);
        sceneManager.AddScene("LoadingGameLevel", scene);
        return scene;
    }
    //exists
    return scene;
}

Scene* GameSceneCreationUtils::GameOverLevel(SceneManager& sceneManager)
{
    Scene* scene = sceneManager.GetScene("GameOver");
    //doesnt exist
    if (scene == nullptr)
    {
        //entity array
        std::map<int, std::vector<Entity*>> entities;

        //screen
        GameOverScreenEntity* gamOverScreen = new GameOverScreenEntity(
            RenderEngine::GetInstanceRenderEngine()->GetScreenCenter(),
            1);
        entities[gamOverScreen->GetRenderLayer()].push_back(gamOverScreen);

        //create scene
        scene = new Scene(entities);

        sceneManager.AddScene("GameOver", scene);
        return scene;
    }
    //exists
    return scene;
}

Scene* GameSceneCreationUtils::GameWinLevel(SceneManager& sceneManager)
{
    Scene* scene = sceneManager.GetScene("Win");

    //doesnt exist
    if (scene == nullptr)
    {
        //entity array
        std::map<int, std::vector<Entity*>> entities;

        //screen
        WinScreenEntity* winScreen = new WinScreenEntity(
            RenderEngine::GetInstanceRenderEngine()->GetScreenCenter(),
            1);
        entities[winScreen->GetRenderLayer()].push_back(winScreen);

        //create scene
        scene = new Scene(entities);
        sceneManager.AddScene("Win", scene);
        return scene;
    }

    //exists
    return scene;
}
