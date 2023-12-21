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
	Node* adhocNode;
	float speed;

public:
	std::vector<Node*> path;
	std::vector<Node*> smoothedPath;
	void Update(float deltaTime);
	void SetDestination(Node* node, NodeMap* nodeMap);
	void Draw();
	void SetNode(Node* node)
	{
		currentNode = node; position = node->position;
	}
	void SetCurrentNode(Node* node)
	{
		currentNode = node;
		node->UpdateOccupiedStatus(true);
	}
	void SetSpeed(float speed) { this->speed = speed; }
	void ClearPath()
	{
		path.clear();
		currentIndex = 0;
	}
	
	Node* GetCurrentNode()
	{
		return currentNode;
	}

	void SetNodeAtMinimumDistance(NodeMap* nodeMap, glm::vec2 referencePosition, float minDistance);

	glm::vec2 GetPosition() { return position; }
};