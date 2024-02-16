#include "ABDecision.h"
#include <iostream>
void ABDecision::MakeDecision(Agent* agent, float deltaTime) 
{
	if (condition->IsTrue(agent))
	{
		A->MakeDecision(agent, deltaTime);
	}
	else 
	{
		B->MakeDecision(agent, deltaTime);
	}
}