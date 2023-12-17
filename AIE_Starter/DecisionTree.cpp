#include "DecisionTree.h"

void DecisionTree::MakeDecision(Agent* agent, float deltaTime)
{
	for (Decision* decision : GetDecisions())
	{
		decision->EvaluateCondition();
	}
}