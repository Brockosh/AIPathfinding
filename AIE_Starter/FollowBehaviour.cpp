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
	if (dist > agent->GetNodeMap()->GetCellSize())
	{
		lastTargetPosition = target->GetPosition();
		agent->GoTo(lastTargetPosition);
	}

}
