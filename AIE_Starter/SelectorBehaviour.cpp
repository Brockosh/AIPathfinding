#include "SelectorBehaviour.h"
#include "Agent.h"
#include "glm/glm.hpp"

void SelectorBehaviour::Update(Agent* agent, float deltaTime)
{
    // Calculate the distance between the agent and its target
    float agentDistFromTargetPosition = glm::distance(agent->GetPosition(), agent->GetTargetAgent()->GetPosition());
    // Determine the threshold for changing behaviour based on cell size
    float behaviourChangeThreshhold = agent->GetNodeMap()->GetCellSize() * 5;

    // If the agent is within the threshold distance, switch to behaviour1
    if (agentDistFromTargetPosition < behaviourChangeThreshhold)
    {
        SetBehaviour(behaviour1, agent);
        agent->SetColor(RED);
    }
    // Otherwise, switch to behaviour2 
    else
    {
        SetBehaviour(behaviour2, agent);
        agent->SetColor(BLUE);
    }
    // Update the currently selected behaviour
    selectedBehaviour->Update(agent, deltaTime);
}

void SelectorBehaviour::SetBehaviour(Behaviour* b, Agent* agent)
{
    // Only change behaviour if it's different from the current one
    if (selectedBehaviour != b)
    {
        selectedBehaviour = b;
        agent->Reset();
    }
}