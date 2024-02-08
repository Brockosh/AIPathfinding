#include "PathAgent.h"
#include "glm/glm.hpp"


void PathAgent::Update(float deltaTime)
{
	if (path.empty()) return;

	float distance = glm::distance(path[currentIndex]->position, position);
	glm::vec2 dir = glm::normalize(path[currentIndex]->position - position);

	float move = distance - (speed * deltaTime);

	if (move > 0)
	{
		position += speed * deltaTime * dir;
		return;
	}

	currentIndex++;

	if (currentIndex >= path.size())
	{
		//Maybe add back in
		//position = path[path.size() - 1]->position;

		path.clear();

		return;
	}

	move *= -1;

	glm::vec2 newDir = glm::normalize(path[currentIndex]->position - path[currentIndex - 1]->position);

	position += move * deltaTime * newDir;

}

void PathAgent::SetDestination(Node* node, NodeMap* nodeMap)
{
	destinationNode = node;
	std::cout << "NEW DES NODE SET" << std::endl;
	if (adhocNode != nullptr) delete adhocNode;
	adhocNode = new Node((float)this->GetPosition().x, (float)this->GetPosition().y);
	path = NodeMap::DijkstrasSearch(currentNode, node, adhocNode);
	//path = NodeMap::DijkstrasSearch(new Node(position.x, position.y), adhocNode);
	//smoothedPath = nodeMap->SmoothPath(path);
	currentIndex = 0;
}

void PathAgent::Draw()
{
	DrawCircle((int)position.x, (int)position.y, 12, YELLOW);
}

void PathAgent::SetNodeAtMinimumDistance(NodeMap* nodeMap, glm::vec2 referencePosition, float minDistance) 
{
	Node* suitableNode = nullptr;
	do 
	{
		// Get a random node from the node map
		suitableNode = nodeMap->GetRandomNode();

		// Check if the node is at least minDistance away from the reference position
		if (glm::distance(referencePosition, suitableNode->position) >= minDistance) 
		{
			break; // Suitable node found
		}
	} while (true);

	// Set the found node
	SetNode(suitableNode);
}


bool PathAgent::IsMovingTowardsDestinationRight() {
	if (!currentNode || path.empty()) 
	{
		// No current node or path is empty, can't determine direction.
		// Return the last known direction 
		return lastMovementWasRight; 
	}

	// Assuming destinationNode is defined somewhere correctly
	if (!destinationNode) 
	{
		// No destination node defined, can't determine direction.
		// Return the last known direction instead of false
		return lastMovementWasRight; 
	}

	// Tolerance to minimize jitter
	float directionTolerance = 0.01f; 
	float deltaX = destinationNode->position.x - currentNode->position.x;

	if (std::abs(deltaX) > directionTolerance) 
	{   // Only consider movement if it's significant
		// Update the last known direction based on current movement
		lastMovementWasRight = deltaX > 0; 
	}

	// Return the last known direction instead of false when the difference is within the tolerance
	return lastMovementWasRight;
}

//void PathAgent::SetNode(Node* node)
//{
//	//void SetNode(Node * node) { currentNode = node; position = node->position; }
//
//	if (node)
//	{
//		currentNode = node;
//		position = node->position;
//	}
//	else
//	{
//
//	}
//}