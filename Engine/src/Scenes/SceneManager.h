#pragma once
#include <map>

#include "Scene.h"

class SceneManager
{
private:
    std::map<std::string, Scene*> scenes;

public:
    
    /// Generic way to get a scene
    Scene* GetScene(std::string sceneName);
    void AddScene(std::string sceneName,Scene* scene);
    void DeleteScene(std::string scene);
    void DeleteAllScenes();
    void DeleteAllScenes(std::string scene);
};
