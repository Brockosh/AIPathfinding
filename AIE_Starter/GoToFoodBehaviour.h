#pragma once
#include "Behaviour.h"

class GoToFoodBehaviour :
    public Behaviour
{
    bool hasRun = false;
    virtual void Update(Agent* agent, float deltaTime);
    virtual void Enter(Agent* agent);
};