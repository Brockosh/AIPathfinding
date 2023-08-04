#pragma once
#include "Behaviour.h"

class GoToPointBehaviour :
    public Behaviour
{
public:
    virtual void Update(Agent* agent, float deltaTime);

};

