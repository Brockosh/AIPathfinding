#include "SelectorBehaviour.h"
#include "Agent.h"
#include "glm/glm.hpp"

void SelectorBehaviour::Update(Agent* agent, float deltaTime)
{
	float agentDistFromTargetPosition = glm::distance(agent->GetPosition(), agent->GetTargetAgent()->GetPosition());
	float behaviourChangeThreshhold = agent->GetNodeMap()->GetCellSize() * 5;

	if (agentDistFromTargetPosition < behaviourChangeThreshhold)
	{
		SetBehaviour(behaviour1, agent);
		agent->SetColor(RED);
	}
	else
	{
		SetBehaviour(behaviour2, agent);
		agent->SetColor(BLUE);
	}
	selectedBehaviour->Update(agent, deltaTime);
}

void SelectorBehaviour::SetBehaviour(Behaviour* b, Agent* agent)
{
	if (selectedBehaviour != b)
	{
		selectedBehaviour = b;
		agent->Reset();
	}
}
