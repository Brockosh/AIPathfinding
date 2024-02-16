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
        
        // Ensure the new Food's position is not already occupied by another Food
        while (IsPositionOccupied(newFood->position))
        {
            // If position is occupied, delete the current Food and create a new one
            delete newFood;
            newFood = new Food(nodeMap);
        }
        // Add the new Food to the list of foods
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

// Removes Food objects from the list if they have been eaten
void FoodSpawner::RemoveEatenFoods() 
{
    for (auto it = foods.begin(); it != foods.end(); ) 
    {
        if ((*it)->GetEatenStatus()) 
        {
            // Delete the eaten Food object and remove it from the list
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