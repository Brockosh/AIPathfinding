#include "GameManager.h"
#include "Agent.h"
#include "ScoreTracker.h"

GameManager::GameManager(Agent* player, Agent* e1, Agent* e2, Agent* e3, Agent* e4, ScoreTracker* st)
{
	agentsInGame.push_back(player);
	agentsInGame.push_back(e1);
	agentsInGame.push_back(e2);
	agentsInGame.push_back(e3);
	agentsInGame.push_back(e4);
	scoreTracker = st;
}

void GameManager::ResetGameState()
{
	scoreTracker->ResetPlayerScore();
	for (Agent* agent : agentsInGame)
	{
		agent->MoveToStartingPosition();
		agent->GetPathAgent()->ClearPath();
		agent->SetWasFollowing(false);
	}
}