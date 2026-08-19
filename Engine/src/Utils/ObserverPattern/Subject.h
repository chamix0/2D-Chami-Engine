#pragma once
#include <list>

#include "Observer.h"
#include "../GameUtils/MyEnums.h"

 class Subject
{
private:
    std::list<Observer*> m_observers;

public:
    void AddObserver(Observer* observer)
    {
        m_observers.push_back(observer);
    }

public:
    void RemoveOverserver(Observer* observer)
    {
        m_observers.remove(observer);
    }

protected:
    void NotifyObservers(ObserverEvents action)
    {
        for (Observer* observer : m_observers)
        {
            observer->OnNotify(action);
        }
    }
};
