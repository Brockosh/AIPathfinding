#include "GoToFoodBehaviour.h"
#include "Agent.h"

void GoToFoodBehaviour::Update(Agent* agent, float deltaTime)
{
	agent->SetColor(GREEN);

	float threshold = 20;
	if (glm::distance(agent->GetPathAgent()->GetPosition(), agent->GetNearestFoodPosition()) < threshold)
	{
		agent->SetWasFollowing(false);
		hasRun = false;
		return;
	}

	//float dist = glm::distance(lastTargetPosition, target->GetPosition());
	//if (dist >= agent->GetNodeMap()->GetCellSize() / 2)
	//{
	//	//lastTargetPosition = target->GetPosition();
	//	//Node* node = agent->GetNodeMap()->GetClosestNode(target->GetPosition());
	//	Node* node = agent->GetNodeMap()->GetClosestNode(target->GetPosition());

	//	if (node == nullptr) { return; }

	//	//lastTargetPosition = node->position;
	//	lastTargetPosition = target->GetPosition();
	//}
	if (!hasRun)
	{
		agent->GoTo(agent->GetNearestFoodPosition());
		hasRun = true;
	}

}

void GoToFoodBehaviour::Enter(Agent* agent)
{
	std::cout << "Going to food" << std::endl;

}
