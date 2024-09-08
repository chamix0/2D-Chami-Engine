#pragma once
class TimeManager
{
private:
    //constants
    // double li; //used to measure time
    // double pcFrequency = 0.0;
    const double fixedTick = 1.0 / 60.0;
    const double deadLoopTick = 1.0 / 15.0;

    //variables
    double prevTime, currentTime = 0;
    double deltaTime = 0; //accumulated time
    double FPS = 0;
    double totalTime = 0.0; //real time
    double logicTime = 0.0; //time inside the game
    double timeScale = 1.0; //speed of the game

public:
    TimeManager(double iTimeScale);

    /// \brief takes a measure of the time and updates all the corresponding variables
    void InitSlotsToProcess();

    /// \brief indicates if the game logic should keep updating and subtracts a tick from the delta time
    /// \return true if the game logic should keep updating and false if it should render
    bool ProcessSlots();

    /// \brief updates the logic time 
    /// \return the tick that the game logic has to use
    double LogicWorldSlot();

    //getters and setters
    double GetFixedTick() const;
    double GetTotalTime() const;
    double GetLogicTime() const;
    double GetFps() const;
    double GetTimeScale() const;
    void SetTimeScale(double value);

private:
    double GetTime();
};
