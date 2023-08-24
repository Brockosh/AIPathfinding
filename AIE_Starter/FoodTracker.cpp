#include "FoodTracker.h"

FoodTracker::FoodTracker(Agent* pAgent, FoodSpawner* mySpawner, /*std::vector<Food*> currentFood,*/ NodeMap* nm)
    : playerAgent(pAgent), myFoodSpawner(mySpawner),  /*activeFood(currentFood),*/ nodeMap(nm)
{
}


//bool FoodTracker::IsEatenByAgent(Agent* agent, Food* food)
//{
//    if (agent->IsPlayerAgent() && (agent->GetPosition() == food->position))
//    {
//        food->SetEatenStatus(true);
//        std::cout << "Get eaten brother" << std::endl;
//        return true;
//    }
//}

bool FoodTracker::IsEatenByAgent(Agent* agent, Food* food)
{
    glm::vec2 distanceVec = agent->GetPosition() - food->position;
    float distance = glm::length(distanceVec);

    if (agent->IsPlayerAgent() && distance < 2)  // You decide the threshold
    {
        food->SetEatenStatus(true);
        std::cout << "Get eaten brother" << std::endl;
        return true;
    }
    return false;
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
    activeFood = uneatenFoods; // Replace the old vector with the uneaten foods
}
