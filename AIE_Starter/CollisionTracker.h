#pragma once
#include <vector>

class Agent;
class GameManager;
class CollisionTracker
{

private:
	Agent* playerAgent;
	std::vector<Agent*> chasingAgents;
	GameManager* gameManager;

public:
	CollisionTracker(Agent* player, Agent* e1, Agent* e2, Agent* e3, Agent* e4, GameManager* gm);
	bool IsColliding(Agent* player, Agent* enemy);
	void Update();
};