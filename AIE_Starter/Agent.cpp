#include "Agent.h"

//Agent::Agent()
//{
//}

void Agent::Reset()
{
	pathAgent.path.clear();
}

void Agent::Update(float deltaTime)
{
	if (current != nullptr)
		current->Update(this, deltaTime);
	pathAgent.Update(deltaTime);
	previousPosition = pathAgent.GetPosition();
	agentDrawer.Update(deltaTime);
	//IsMovingRight();
}

void Agent::Draw()
{
	agentDrawer.Draw(*this);
}

void Agent::GoTo(glm::vec2 pos)
{
	Node* end = nodeMap->GetClosestNode(pos);
	if (end == nullptr) { return; }

	Node* node = nodeMap->GetClosestNode(pathAgent.GetPosition());

	if (node == nullptr) { return; }

	pathAgent.SetCurrentNode(node);
	pathAgent.SetDestination(end, nodeMap);
}

glm::vec2 Agent::GetNearestFoodPosition()
{
	glm::vec2 currentPosition = pathAgent.GetPosition();
	float shortestDistance = std::numeric_limits<float>::max(); 
	glm::vec2 nearestFoodPos = { 0, 0 };

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



bool Agent::IsMovingRight() 
{
	glm::vec2 currentPosition = GetPathAgent()->GetPosition();
	/*if (currentPosition.x > previousPosition.x)
	{
		std::cout << "Moving right" << std::endl;
	}
	else
	{
		std::cout << "Moving left" << std::endl;
	}*/
	return currentPosition.x > previousPosition.x;
}