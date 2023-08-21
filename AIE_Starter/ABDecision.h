#pragma once
#include "Decision.h"
#include "Condition.h"
class ABDecision :
    public Decision
{

public:
    Decision* A;
    Decision* B;

    Condition* condition;

    virtual void MakeDecision(Agent* agent, float deltaTime);

};

