#pragma once
#include "Behaviour.h"
#include "Decision.h"
class DecisionBehaviour :
    public Behaviour
{
private:
    Decision* thisDecision;

public:
    DecisionBehaviour(Decision* decision) : thisDecision(decision) {}

    virtual void Update(Agent* agent, float deltaTime) override 
    {
        thisDecision->MakeDecision(agent, deltaTime);
    }
};

