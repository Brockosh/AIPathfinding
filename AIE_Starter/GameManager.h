#pragma once
#include <vector>

class Agent;
class GameManager
{
private:
	std::vector<Agent*> agentsInGame;

public:
	GameManager(Agent* player, Agent* e1, Agent* e2, Agent* e3, Agent* e4);
	void ResetGameState();
};

