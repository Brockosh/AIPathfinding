#include "FoodSpawner.h"
FoodSpawner::FoodSpawner(NodeMap* nm, int foodCount) : nodeMap(nm), desiredFoodCount(foodCount)
{
    SpawnFood(desiredFoodCount);
}

FoodSpawner::~FoodSpawner() {
    for (Food* food : foods) {
        delete food;
    }
}

void FoodSpawner::SpawnFood(int amount) {
    for (int i = 0; i < amount; ++i)
    {
        Food* newFood = new Food(nodeMap);
        
        while (IsPositionOccupied(newFood->position))
        {
            delete newFood;
            newFood = new Food(nodeMap);
        }
        foods.push_back(newFood);
    }
}

bool FoodSpawner::IsPositionOccupied(glm::vec2& position)
{
    for (Food* food : foods)
    {
        if (food->position == position)
        {
            return true;
        }
    }
    return false;
}

void FoodSpawner::RemoveEatenFoods() {
    for (auto it = foods.begin(); it != foods.end(); ) {
        if ((*it)->GetEatenStatus()) {
            delete* it;
            it = foods.erase(it);
        }
        else {
            ++it;
        }
    }
}

void FoodSpawner::UpdateAllFoods() 
{
    if (foods.size() < desiredFoodCount)
    {
        SpawnFood(1);
    }

    for (Food* food : foods) {
        food->Update();
    }
    RemoveEatenFoods(); 
}