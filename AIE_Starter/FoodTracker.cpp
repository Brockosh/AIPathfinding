#include "FoodTracker.h"

FoodTracker::FoodTracker(Agent* pAgent, FoodSpawner* mySpawner, /*std::vector<Food*> currentFood,*/ NodeMap* nm)
    : playerAgent(pAgent), myFoodSpawner(mySpawner),  /*activeFood(currentFood),*/ nodeMap(nm)
{
}

bool FoodTracker::IsEatenByAgent(Agent* agent, Food* food)
{
    glm::vec2 distanceVec = agent->GetPosition() - food->position;
    float distance = glm::length(distanceVec);

    if (agent->IsPlayerAgent() && distance < 30)  
    {
        food->SetEatenStatus(true);
        return true;
    }
    return false;
}

void FoodTracker::Init(Agent* pAgent)
{
    playerAgent = pAgent;
    activeFood = myFoodSpawner->GetActiveFood();
}


void FoodTracker::Update()
{
    activeFood = myFoodSpawner->GetActiveFood();

    // Iterate through all active food items and check if they've been eaten
    for (Food* food : activeFood)
    {
        IsEatenByAgent(playerAgent, food);
    }

    // Remove eaten foods from the activeFood vector
    std::vector<Food*> uneatenFoods;
    for (Food* food : activeFood)
    {
        if (!food->GetEatenStatus())
        {
            uneatenFoods.push_back(food);
        }
    }
    // Replace the old vector with the uneaten foods
    activeFood = uneatenFoods; 
}