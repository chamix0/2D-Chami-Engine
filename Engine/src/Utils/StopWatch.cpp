// Fill out your copyright notice in the Description page of Project Settings.


#include "StopWatch.h"

void StopWatch::Stop()
{
    stopped = true;
}

void StopWatch::Reset()
{
    stopped = true;
    accumulatedTime = 0.f;
}

void StopWatch::Start()
{
    if (stopped)
    {
        stopped = false;
    }
}

bool StopWatch::isRunning() const
{
    return !stopped;
}

float StopWatch::GetElapsedSeconds() const
{
    return accumulatedTime;
}

float StopWatch::GetElapsedMiliSeconds() const
{
    return GetElapsedSeconds() * 1000.f;
}

void StopWatch::AddElapsedTime(float val)
{
    accumulatedTime += val;
}

void StopWatch::ReStart()
{
    stopped = false;
    accumulatedTime = 0;
}

StopWatch::StopWatch(): accumulatedTime(0), stopped(true)
{
}


void StopWatch::ReceiveTick(float deltaTime)
{
    if (!stopped)
    {
        accumulatedTime += deltaTime;
    }
}
