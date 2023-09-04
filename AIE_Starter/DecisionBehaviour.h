//#pragma once
//#include "Behaviour.h"
//#include "Decision.h"
//class DecisionBehaviour :
//    public Behaviour
//{
//private:
//    Decision* thisDecision;
//
//public:
//    DecisionBehaviour(Decision* decision) : thisDecision(decision) {}
//
//    virtual void Update(Agent* agent, float deltaTime) override 
//    {
//        thisDecision->MakeDecision(agent, deltaTime);
//    }
//};
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