#include "glfw3.h"
#include "Engine_Managers/AudioManager.h"
#include "Engine_Managers/RenderEngine.h"
#include "Engine_Managers/LogicManager.h"
#include "Engine_Managers/TimeManager.h"
#include "Engine_Managers/Input/InputManager.h"

using namespace std;

int main()
{
    //make the game random
    srand((unsigned int)time(NULL));

    //Game logic stuff
    TimeManager timer(1);
    InputManager input_manager = InputManager();
    LogicManager* logicManager = LogicManager::GetInstanceLogicManager();
    RenderEngine* renderEngine = RenderEngine::GetInstanceRenderEngine();
    AudioManager* audioManager = AudioManager::GetInstanceAudioManager();

    //initialization
    audioManager->Init();
    renderEngine->Init();
    logicManager->Init();

    //get current window
    GLFWwindow* window = glfwGetCurrentContext(); //window reference

    //update
    while (!glfwWindowShouldClose(window))
    {
        //read player input
        logicManager->UpdateInputs(&input_manager);

        //update game logic
        logicManager->UpdateGameLogic(timer);

        //update render
        renderEngine->UpdateRender(timer);

        //Process events
        glfwPollEvents();
    }

    //shut down
    renderEngine->ShutDown();
    logicManager->ShutDown();
    audioManager->ShutDown();

    //delete managers
    delete logicManager;
    delete renderEngine;
    delete audioManager;

    return 0;
}
