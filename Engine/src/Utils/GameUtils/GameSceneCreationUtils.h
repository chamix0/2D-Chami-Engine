#pragma once

class Scene;

class GameSceneCreationUtils
{
public:
    
    //game scenes
    static Scene* GetMainMenu(SceneManager& sceneManager);
    static Scene* GetRegularGameLevel(SceneManager& sceneManager);

    static Scene* GetGameLevel(SceneManager& sceneManager);
    static Scene* GetDialogueLevel(SceneManager& sceneManager, int mode, int dificulty = 0);
    static Scene* LoadingGameLevel(SceneManager& sceneManager);
    static Scene* GameOverLevel(SceneManager& sceneManager);
    static Scene* GameWinLevel(SceneManager& sceneManager);
};
