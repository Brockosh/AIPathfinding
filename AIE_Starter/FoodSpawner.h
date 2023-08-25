#pragma once

#include <vector>
#include "Food.h"

class FoodSpawner {
private:
    NodeMap* nodeMap;
    std::vector<Food*> foods;
    int desiredFoodCount;

public:
    FoodSpawner(NodeMap* nm, int foodCount);
    ~FoodSpawner();

    void SpawnFood(int amount);
    bool IsPositionOccupied(glm::vec2& position);
    std::vector<Food*> GetActiveFood() { return foods; }
    void RemoveEatenFoods();
    void UpdateAllFoods();
};

