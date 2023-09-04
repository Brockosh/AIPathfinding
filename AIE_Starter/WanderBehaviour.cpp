#include "WanderBehaviour.h"
#include "Agent.h"
void WanderBehaviour::Update(Agent* agent, float deltaTime)
{
	if (!agent->PathComplete())
	{
		return;
	}
	
	agent->GoTo(agent->GetNodeMap()->GetRandomNode()->position);
	
}

void WanderBehaviour::Enter(Agent* agent)
{
	agent->SetColor(BLUE);

	
}
