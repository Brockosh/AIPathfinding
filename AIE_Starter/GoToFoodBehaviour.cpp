#include "GoToFoodBehaviour.h"
#include "Agent.h"

void GoToFoodBehaviour::Update(Agent* agent, float deltaTime)
{
	agent->SetColor(GREEN);

	float threshold = 200;
	if (glm::distance(agent->GetPathAgent()->GetPosition(), agent->GetNearestFoodPosition()) < threshold)
	{
		agent->SetWasFollowing(false);
		hasRun = false;
		return;
	}

	if (!hasRun)
	{
		agent->GoTo(agent->GetNearestFoodPosition());
		hasRun = true;
	}

}

void GoToFoodBehaviour::Enter(Agent* agent)
{
}