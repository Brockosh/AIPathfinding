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
	DrawCircle((int)pathAgent.GetPosition().x, (int)pathAgent.GetPosition().y, 12, color);
}

void Agent::GoTo(glm::vec2 pos)
{
	Node* end = nodeMap->GetClosestNode(pos);
	pathAgent.SetNode(nodeMap->GetClosestNode(pathAgent.GetPosition()));
	pathAgent.SetDestination(end, nodeMap);
}
