#pragma once
#include <map>

#include "Scene.h"

class SceneManager
{
private:
    std::map<std::string, Scene*> scenes;

public:
    // static Scene* LoadScene(int index);
    Scene* LoadInputsScene();

    //game scenes
    Scene* GetMainMenu();
    Scene* GetGameLevel();
    Scene* GetDialogueLevel(int mode, int dificulty = 0);
    Scene* LoadingGameLevel();
    Scene* GameOverLevel();
    Scene* GameWinLevel();

    //exercises scenes
    Scene* GetP1Scene();
    Scene* GetP2Scene();
    Scene* GetP3Scene();
    Scene* GetP4Scene();
    Scene* GetP5Scene();
    Scene* GetP6Scene();
    Scene* GetP7Scene();

    Scene* GetScene(std::string sceneName);

    void DeleteScene(std::string scene);
    void DeleteAllScenes();
    void DeleteAllScenes(std::string scene);
};
