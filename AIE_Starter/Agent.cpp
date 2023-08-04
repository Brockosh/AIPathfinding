#include "Agent.h"

Agent::Agent()
{
}

void Agent::Update(float deltaTime)
{
	if (current != nullptr)
		current->Update(this, deltaTime);
	pathAgent.Update(deltaTime);
}

void Agent::Draw()
{
	pathAgent.Draw();
}

void Agent::GoTo(glm::vec2 pos)
{
	Node* end = nodeMap->GetClosestNode(pos);
	pathAgent.SetNode(nodeMap->GetClosestNode(pathAgent.GetPosition()));
	pathAgent.SetDestination(end);
}
