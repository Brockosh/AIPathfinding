#pragma once
#include "Condition.h"

class Agent;
class Condition;

class Decision
{
private:
	Agent* agent;
	Condition* condition;

public:
	bool EvaluateCondition() { return condition->IsTrue(agent); };
	virtual void MakeDecision(Agent* agent, float deltaTime) = 0;
};