#include "Agent.h"
#include "PathAgent.h"

void Agent::Reset()
{
	pathAgent.path.clear();
}

void Agent::Update(float deltaTime)
{
    // Update current behavior if available
    if (current != nullptr)
        current->Update(this, deltaTime);

    // Make decisions if a decision tree is set
    if (decisionRoot != nullptr)
        decisionRoot->MakeDecision(this, deltaTime);

    pathAgent.Update(deltaTime);
    agentDrawer.Update(deltaTime);
}


void Agent::Draw()
{
    agentDrawer.Draw(*this);
}


void Agent::GoTo(glm::vec2 pos)
{
    // Find the closest node to the target position
    Node* end = nodeMap->GetClosestNode(pos);
    if (end == nullptr) return;

    // Find the closest node to the agent's current position
    Node* node = nodeMap->GetClosestNode(pathAgent.GetPosition());
    if (node == nullptr) return;

    // Set the path from the agent's current node to the destination node
    pathAgent.SetCurrentNode(node);
    pathAgent.SetDestination(end, nodeMap);
}


glm::vec2 Agent::GetNearestFoodPosition()
{
    glm::vec2 currentPosition = pathAgent.GetPosition();
    float shortestDistance = std::numeric_limits<float>::max();
    glm::vec2 nearestFoodPos = { 0, 0 };

    // Find the closest active food item
    for (Food* food : myFoodSpawner->GetActiveFood())
    {
        glm::vec2 diff = food->position - currentPosition;
        float distance = glm::length(diff);

        if (distance < shortestDistance)
        {
            shortestDistance = distance;
            nearestFoodPos = food->position;
        }
    }

    return nearestFoodPos;
}

void Agent::SetStartingNodeAtMinimumDistance(NodeMap* nodeMap, glm::vec2 referencePosition, float minDistance) 
{
	pathAgent.SetNodeAtMinimumDistance(nodeMap, referencePosition, minDistance);
	this->startingPosition = pathAgent.GetCurrentNode(); 
}

bool Agent::IsMovingRight() 
{
	glm::vec2 currentPosition = GetPathAgent()->GetPosition();
	return currentPosition.x > previousPosition.x;
}