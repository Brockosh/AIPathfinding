#pragma once
#include <glm/fwd.hpp>
#include <vector>
#include "Pathfinding.h"
#include "NodeMap.h"

using namespace AIForGames;

class PathAgent
{

private:
	glm::vec2 position;
	int currentIndex;
	Node* currentNode;
	float speed;

public:
	std::vector<Node*> path;
	void Update(float deltaTime);
	void SetDestination(Node* node);
	void Draw();
	void SetNode(Node* node) { currentNode = node; position = node->position; }
	void SetSpeed(float speed) { this->speed = speed; }


	glm::vec2 GetPosition() { return position; }
};

