#include "GameManager.h"
#include "Agent.h"

GameManager::GameManager(Agent* player, Agent* e1, Agent* e2, Agent* e3, Agent* e4)
{
	agentsInGame.push_back(player);
	agentsInGame.push_back(e1);
	agentsInGame.push_back(e2);
	agentsInGame.push_back(e3);
	agentsInGame.push_back(e4);
}

void GameManager::ResetGameState()
{
	for (Agent* agent : agentsInGame)
	{
		//agent->MoveToStartingPosition();
	}
}
