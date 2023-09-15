#pragma once
#include <vector>

class Agent;
class ScoreTracker;
class GameManager
{
private:
	std::vector<Agent*> agentsInGame;
	ScoreTracker* scoreTracker;

public:
	GameManager(Agent* player, Agent* e1, Agent* e2, Agent* e3, Agent* e4, ScoreTracker* st);
	void ResetGameState();
};