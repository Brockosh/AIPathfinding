#pragma once
#include "Behaviour.h"

class WanderBehaviour :
    public Behaviour
{
    virtual void Update(Agent* agent, float deltaTime);
    virtual void Enter(Agent* agent);
};