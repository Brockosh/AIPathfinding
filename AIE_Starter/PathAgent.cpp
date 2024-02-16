#include "PathAgent.h"
#include "glm/glm.hpp"


void PathAgent::Update(float deltaTime)
{
    // Exit early if there is no path to follow
    if (path.empty()) return;

    // Calculate the distance to the next node in the path
    float distance = glm::distance(path[currentIndex]->position, position);
    // Determine the direction vector towards the next node
    glm::vec2 dir = glm::normalize(path[currentIndex]->position - position);

    // Calculate the remaining distance after moving this frame
    float move = distance - (speed * deltaTime);

    // If there is distance left to move towards the current target node, move and exit
    if (move > 0)
    {
        position += speed * deltaTime * dir;
        return;
    }

    // Move to the next node in the path
    currentIndex++;

    // If all nodes in the path have been visited, clear the path
    if (currentIndex >= path.size())
    {
        path.clear();
        return;
    }

    // Adjust for overshooting the previous target node
    move *= -1;

    // Calculate the new direction towards the next target node
    glm::vec2 newDir = glm::normalize(path[currentIndex]->position - path[currentIndex - 1]->position);

    // Move the agent along the new direction by the adjusted amount
    position += move * deltaTime * newDir;
}

// SetDestination method updates the agent's target destination and recalculates the path.
void PathAgent::SetDestination(Node* node, NodeMap* nodeMap)
{
    // Set the new destination node
    destinationNode = node;
    // Clean up the previous ad-hoc node, if any
    if (adhocNode != nullptr) delete adhocNode;
    // Create a new ad-hoc node at the agent's current position
    adhocNode = new Node((float)this->GetPosition().x, (float)this->GetPosition().y);
    // Recalculate the path using Dijkstra's algorithm
    path = NodeMap::DijkstrasSearch(currentNode, node, adhocNode);
    // Reset the path traversal index
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