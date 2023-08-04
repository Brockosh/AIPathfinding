#pragma once
#include "Behaviour.h"
//#include "agent.h"
//#include "NodeMap.h"
class WanderBehaviour :
    public Behaviour
{
    virtual void Update(Agent* agent, float deltaTime);
};

