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
}

//void Agent::Update(float deltaTime)
//{
//	if (decisionRoot != nullptr)
//		decisionRoot->MakeDecision(this, deltaTime);
//	pathAgent.Update(deltaTime);
//}

void Agent::Draw()
{
	if (!isPlayerAgent)
	DrawCircle((int)pathAgent.GetPosition().x, (int)pathAgent.GetPosition().y, 12, color);
	/*DrawTexture(agentTexture, (int)pathAgent.GetPosition().x, (int)pathAgent.GetPosition().y, WHITE);*/
	else
	{
		Vector2 position = { pathAgent.GetPosition().x - agentTexture.width * 0.5f + 2, pathAgent.GetPosition().y - agentTexture.height * 0.5f + 2 };
		float scale = 0.2f;
		DrawTextureEx(agentTexture, position, 0.0f, scale, WHITE);
	}
}

void Agent::GoTo(glm::vec2 pos)
{
	Node* end = nodeMap->GetClosestNode(pos);
	pathAgent.SetNode(nodeMap->GetClosestNode(pathAgent.GetPosition()));
	pathAgent.SetDestination(end, nodeMap);
}
