#include "Agent.h"

Agent::Agent()
{
}

void Agent::Reset()
{
	pathAgent.path.clear();
}

void Agent::Update(float deltaTime)
{
	if (current != nullptr)
		current->Update(this, deltaTime);
	pathAgent.Update(deltaTime);
	std::cout << startingPosition->position.x << std::endl;
}

//void Agent::Update(float deltaTime)
//{
//	if (decisionRoot != nullptr)
//		decisionRoot->MakeDecision(this, deltaTime);
//	pathAgent.Update(deltaTime);
//}

void Agent::Draw()
{
		DrawCircle((int)pathAgent.GetPosition().x, (int)pathAgent.GetPosition().y, 12, color);
	//if (!isPlayerAgent)
	//{
	//	//DrawTexture(agentTexture, (int)pathAgent.GetPosition().x, (int)pathAgent.GetPosition().y, WHITE);
	//}
	//else
	//{
	//	float scale = 0.2f;
	//	Vector2 position = { pathAgent.GetPosition().x - agentTexture.width * 0.5f * scale, pathAgent.GetPosition().y - agentTexture.height * 0.5f * scale };
	//	DrawTextureEx(agentTexture, position, 0.0f, scale, WHITE);
	//}
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
