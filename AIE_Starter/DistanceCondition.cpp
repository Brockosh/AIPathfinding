#include "DistanceCondition.h"
#include "glm/glm.hpp"
#include "Agent.h"

bool DistanceCondition::IsTrue(Agent* agent)
{
	float dist = glm::distance(agent->GetPosition(), agent->GetTargetAgent()->GetPosition());

	bool answer = (dist < distanceThreshhold) == lessThan;

	return answer;
}
