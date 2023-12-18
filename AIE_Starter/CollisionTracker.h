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
	CollisionTracker(Agent* player, GameManager* gm);
	bool IsColliding(Agent* player, Agent* enemy);
	void Update();
	void Init(Agent* player, std::vector<Agent*>& enemies);
};