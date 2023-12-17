#pragma once

#include "glm/glm.hpp"
#include "NodeMap.h"
class Food
{

	NodeMap* nodeMap;
	bool isEaten;

public:
	glm::vec2 position;
	Texture2D foodTexture = LoadTexture("MyImages/Burger.png");
	Food(NodeMap* nm);
	void Update();
	NodeMap* GetNodeMap() { return nodeMap; }
	bool GetEatenStatus() { return isEaten; }
	void SetEatenStatus(bool eatenStatus) { isEaten = eatenStatus; }
};