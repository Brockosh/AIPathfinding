#pragma once

#include "glm/glm.hpp"
#include "NodeMap.h"
class Food
{

	NodeMap* nodeMap;
	bool isEaten;

public:
	glm::vec2 position;
	Food(NodeMap* nm);
	void Update();
	NodeMap* GetNodeMap() { return nodeMap; }
	bool GetEatenStatus() { return isEaten; }
	void SetEatenStatus(bool eatenStatus) { isEaten = eatenStatus; }
};