#pragma once
#include <map>

#include "Scene.h"

class SceneManager
{
private:
    std::map<std::string, Scene*> scenes;

public:
    // static Scene* LoadScene(int index);
    // Scene* LoadInputsScene();

    // //game scenes
    // Scene* GetMainMenu();
    // Scene* GetGameLevel();
    // Scene* GetDialogueLevel(int mode, int dificulty = 0);
    // Scene* LoadingGameLevel();
    // Scene* GameOverLevel();
    // Scene* GameWinLevel();



    /// Generic way to get a scene
    Scene* GetScene(std::string sceneName);
    void AddScene(std::string sceneName,Scene* scene);
    void DeleteScene(std::string scene);
    void DeleteAllScenes();
    void DeleteAllScenes(std::string scene);
};
