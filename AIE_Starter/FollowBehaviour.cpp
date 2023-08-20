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
	if (dist >= agent->GetNodeMap()->GetCellSize())
	{
		//lastTargetPosition = target->GetPosition();
		lastTargetPosition = agent->GetNodeMap()->GetClosestNode(target->GetPosition())->position;
		agent->GoTo(lastTargetPosition);
	}

}

void FollowBehaviour::Enter(Agent* agent)
{
	agent->SetColor(RED);
}
