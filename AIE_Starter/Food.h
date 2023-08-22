#pragma once

#include "glm/glm.hpp"
#include "NodeMap.h"
class Food
{

	NodeMap* nodeMap;

public:
	glm::vec2 position;
	Food(NodeMap* nm);
	void Update();
	NodeMap* GetNodeMap() { return nodeMap; }
};

