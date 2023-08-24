#include "FoodSpawner.h"
FoodSpawner::FoodSpawner(NodeMap* nm) : nodeMap(nm) 
{
    SpawnFood(4);
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
        foods.push_back(newFood);
    }
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

void FoodSpawner::UpdateAllFoods() {
    for (Food* food : foods) {
        food->Update();
    }
    RemoveEatenFoods(); 
}