#pragma once
#include <vector>

#include "../Entities/Entity.h"
#include "../Scenes/Scene.h"
#include "../Scenes/SceneManager.h"
#include "Input/InputManager.h"


class TimeManager;
class MyEntity;

class LogicManager
{
private:
    static LogicManager* logicInstance; //singleton instance
    Scene* currentScene = nullptr;
    TimeManager* timeManager;
    SceneManager sceneManager;

public:
    /// \brief Singleton
    /// \return 
    static LogicManager* GetInstanceLogicManager();

    /// \brief Initialize first scene and game logic stuff 
    void Init();

    /// \brief updates the state of state of the game
    /// \param timer 
    void UpdateGameLogic(TimeManager& timer);

    /// \brief listen inputs every frame
    void UpdateInputs(InputManager* input_manager);

    /// \brief checks collisions every frame
    void UpdateCollisions(Entity* entity);

    /// \brief un initialize 
    void ShutDown();

    /// \brief sets the time scale of the game to 0 or 1 depending on if it is paused or not
    /// \param pause 
    void SetPause(bool pause);
    bool GetPaused();

    TimeManager* GetTimeManager() const;
    SceneManager* GetSceneManager();
    void SetCurrentScene(Scene* scene);
    Scene* GetCurrentScene() const;;
    //helpers
    /// \brief Get all entities in a map
    /// \return 
    std::map<int, std::vector<Entity*>> GetEntities();
    /// \brief Get all entities in an array
    /// \return 
    std::vector<Entity*> GetEntitiesArray();
    /// \brief Get current scene camera
    /// \return 
    Camera* GetCamera();
    /// \brief find all entities in the current scene with a tag
    /// \param tag 
    /// \return 
    std::vector<Entity*> FindEntitiesWithTag(std::string tag);

    /// \brief close the window and the aplication
    /// 
    void ExitAplication();


private:

};
