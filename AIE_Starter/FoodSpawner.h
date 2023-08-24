#pragma once

#include <vector>
#include "Food.h"

class FoodSpawner {
private:
    NodeMap* nodeMap;
    std::vector<Food*> foods;

public:
    FoodSpawner(NodeMap* nm);
    ~FoodSpawner();

    void SpawnFood(int amount);
    std::vector<Food*> GetActiveFood() { return foods; }
    void RemoveEatenFoods();
    void UpdateAllFoods();
};

