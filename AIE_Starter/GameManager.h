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
#include "GameState.h"
#include "MainMenu.h"
#include "EndGameMenu.h"
#include "MusicManager.h"

class GameManager {
private:
    bool isQuitting = false;
    std::vector<Agent*> agentsInGame;
    Agent* playerAgent;
    std::vector<Agent*> enemyAgents;
    FoodSpawner foodSpawner;
    PlayerScore playerScore;
    ScoreTracker scoreTracker;
    FoodTracker foodTracker;
    CollisionTracker collisionTracker;
    MainMenu mainMenu;
    EndGameMenu endGameMenu;
    MusicManager musicManager;
    GameState gameState;

public:
	GameManager(NodeMap* nodeMap, int numberOfEnemies, float playerSpeed, float enemySpeed, int foodAmount);

    NodeMap* nodeMap;
    NodeMap* GetNodeMap() { return nodeMap; }
    ABDecision* SetupEnemyDecisionTree();
    bool IsQuitting() const { return isQuitting; }
    void SetQuitting(bool quitting) { isQuitting = quitting; }
    void SetPlayerScore(int score) { playerScore.SetScore(score); }
	void Update(float deltaTime);
    void Draw();
	void ResetGameState();
    void SwitchToMainMenu();
    void SwitchToEndGameMenu();
};