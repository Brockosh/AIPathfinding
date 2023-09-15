#include "LostTargetCondition.h"
#include "Agent.h"

bool LostTargetCondition::IsTrue(Agent* agent)
{
    Agent* target = agent->GetTargetAgent();
    if (target == nullptr) return false;

    glm::vec2 agentPos = agent->GetPosition();
    glm::vec2 targetPos = target->GetPosition();

    float dist = glm::length(targetPos - agentPos);

    return agent->WasFollowing() && dist >= distanceThreshold;
}
