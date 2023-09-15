#pragma once
#include "Behaviour.h"
#include "Decision.h"

class DecisionBehaviour : public Decision {
private:
    Behaviour* thisBehaviour;

public:
    DecisionBehaviour(Behaviour* behaviour) : thisBehaviour(behaviour) {}

    virtual void MakeDecision(Agent* agent, float deltaTime) override
    {
        thisBehaviour->Enter(agent);
        thisBehaviour->Update(agent, deltaTime);
    }
};