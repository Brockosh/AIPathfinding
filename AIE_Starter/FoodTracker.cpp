#include "FoodTracker.h"

FoodTracker::FoodTracker(Agent* pAgent, FoodSpawner* mySpawner,NodeMap* nm)
    : playerAgent(pAgent), myFoodSpawner(mySpawner), nodeMap(nm)
{}

bool FoodTracker::IsEatenByAgent(Agent* agent, Food* food)
{
    // Calculate the distance between the agent and the food
    glm::vec2 distanceVec = agent->GetPosition() - food->position;
    float distance = glm::length(distanceVec);

    // If the agent is the player and is close enough to the food, consider the food eaten
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
    // Update the list of active food items
    activeFood = myFoodSpawner->GetActiveFood();

    // Check each food item to see if it's been eaten by the player agent
    for (Food* food : activeFood)
    {
        IsEatenByAgent(playerAgent, food);
    }

    // Filter out the eaten foods from the activeFood list
    std::vector<Food*> uneatenFoods;
    for (Food* food : activeFood)
    {
        if (!food->GetEatenStatus())
        {
            uneatenFoods.push_back(food);
        }
    }
    // Update the activeFood list to only include uneaten foods
    activeFood = uneatenFoods;
}