#pragma once
#include "Decision.h"
#include "Condition.h"
#include <vector>
class DecisionTree
{
    std::vector<Decision*> decisions;
    std::vector<Condition*> conditions;
    
    std::vector<Decision*> GetDecisions() { return decisions; }

public:

    void MakeDecision(Agent* agent, float deltaTime);
};