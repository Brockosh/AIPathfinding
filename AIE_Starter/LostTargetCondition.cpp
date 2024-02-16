#include "LostTargetCondition.h"
#include "Agent.h"

bool LostTargetCondition::IsTrue(Agent* agent)
{
    Agent* target = agent->GetTargetAgent();
    // If there is no target, the condition is not met
    if (target == nullptr) return false;

    // Get positions of the agent and its target
    glm::vec2 agentPos = agent->GetPosition();
    glm::vec2 targetPos = target->GetPosition();

    // Calculate the distance between the agent and its target
    float dist = glm::length(targetPos - agentPos);

    return agent->WasFollowing() && dist >= distanceThreshold;
}