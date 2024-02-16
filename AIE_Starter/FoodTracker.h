#pragma once
#include <vector>
#include "Food.h"
#include "Agent.h"
#include "FoodSpawner.h"
class FoodTracker
{
	Agent* playerAgent;
	std::vector<Food*> activeFood;
	NodeMap* nodeMap;
	FoodSpawner* myFoodSpawner;

public:
	FoodTracker(Agent* pAgent, FoodSpawner* mySpawner, NodeMap* nm);
	bool IsEatenByAgent(Agent* agent, Food* food);
	void Update();
	void Init(Agent* pAgent);
};