#pragma once
#include "NodeMap.h"
#include "Agent.h"
#include "FoodSpawner.h"
#include "FoodTracker.h"
#include "ScoreTracker.h"
#include "CollisionTracker.h"
#include "PlayerScore.h"
#include "Behaviour.h"
#include "ABDecision.h"
#include <vector>

class GameManager {
private:
    std::vector<Agent*> agentsInGame;
    Agent* playerAgent;
    std::vector<Agent*> enemyAgents;
    FoodSpawner foodSpawner;
    PlayerScore playerScore;
    ScoreTracker scoreTracker;
    FoodTracker foodTracker;
    CollisionTracker collisionTracker;

public:
    NodeMap* nodeMap;
	GameManager(NodeMap* nodeMap, int numberOfEnemies, float playerSpeed, float enemySpeed, int foodAmount);
    ABDecision* SetupEnemyDecisionTree();
    NodeMap* GetNodeMap() { return nodeMap; }
	void Update(float deltaTime);
    void Draw();
	void ResetGameState();
};