#include "ABDecision.h"
#include <iostream>
void ABDecision::MakeDecision(Agent* agent, float deltaTime) 
{
	if (condition->IsTrue(agent))
	{
		A->MakeDecision(agent, deltaTime);
		
		//std::cout << "Decision A chosen" << std::endl;
	}
	else 
	{
		B->MakeDecision(agent, deltaTime);
		//std::cout << "Decision B chosen" << std::endl;
	}
}