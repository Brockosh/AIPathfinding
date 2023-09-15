#include "FollowBehaviour.h"
#include "Agent.h"
void FollowBehaviour::Update(Agent* agent, float deltaTime)
{
	Agent* target = agent->GetTargetAgent();
	if (target == nullptr)
	{
		std::cout << "Target agent is null\n";
		return;
	}

	float dist = glm::distance(lastTargetPosition, target->GetPosition());
	if (dist >= agent->GetNodeMap()->GetCellSize() / 4)
	{
		//lastTargetPosition = target->GetPosition();
		//Node* node = agent->GetNodeMap()->GetClosestNode(target->GetPosition());
		Node* node = agent->GetNodeMap()->GetClosestNode(target->GetPosition());

		if (node == nullptr) { return; }

		//lastTargetPosition = node->position;
		lastTargetPosition = target->GetPosition();
		agent->GoTo(lastTargetPosition);
	}
	agent->SetWasFollowing(true);
}

void FollowBehaviour::Enter(Agent* agent)
{
	agent->SetColor(RED);
}