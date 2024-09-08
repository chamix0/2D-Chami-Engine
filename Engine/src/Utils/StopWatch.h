#pragma once

class StopWatch
{
private:
    float accumulatedTime = 0;
    bool stopped = true;

public:
    StopWatch();

public:
    void ReceiveTick(float deltaTime);
    /// stops the stopwatch
    void Stop();
    //resets the stop watch and stops it
    void Reset();
    //starts the stopwatch if it was stopped
    void Start();
    /// 
    /// @return true if is runing
    bool isRunning() const;
    /// 
    /// @return accumulated seconds
    float GetElapsedSeconds() const;
    //accumulated miliseconds
    float GetElapsedMiliSeconds() const;
    void AddElapsedTime(float val);
    void ReStart();
};
