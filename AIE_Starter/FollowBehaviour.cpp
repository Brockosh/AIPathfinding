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

    // Calculate the distance between the agent and the target
    float dist = glm::distance(lastTargetPosition, target->GetPosition());

    // If the distance is greater than or equal to a quarter of the cell size, move towards the target
    if (dist >= agent->GetNodeMap()->GetCellSize() / 4)
    {
        Node* node = agent->GetNodeMap()->GetClosestNode(target->GetPosition());

        if (node == nullptr) { return; }

        lastTargetPosition = target->GetPosition();
        agent->GoTo(lastTargetPosition);
    }
    agent->SetWasFollowing(true);
}

void FollowBehaviour::Enter(Agent* agent)
{
}