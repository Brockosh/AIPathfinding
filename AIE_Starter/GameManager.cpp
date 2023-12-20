#include "GameManager.h"
#include "Agent.h"
#include "ScoreTracker.h"
#include "GoToPointBehaviour.h"
#include "WanderBehaviour.h"
#include "FollowBehaviour.h"
#include "GoToFoodBehaviour.h"
#include "DistanceCondition.h"
#include "LostTargetCondition.h"
#include "DecisionBehaviour.h"

GameManager::GameManager(NodeMap* nodeMap, int enemyCount, float playerSpeed, float enemySpeed, int foodAmount)
    : nodeMap(nodeMap),
    foodSpawner(nodeMap, foodAmount),
    playerScore(),
    scoreTracker(&foodSpawner, &playerScore),
    foodTracker(nullptr, &foodSpawner, nodeMap),
    collisionTracker(nullptr, this),
    mainMenu(),
    endGameMenu()

{
    gameState = GameState::MainMenu;

    // Gotta fix this to predetermine starting positions
    Node* playerStartNode = nodeMap->GetRandomNode(); 
    playerAgent = new Agent(nodeMap, new GoToPointBehaviour(), playerStartNode, playerSpeed, true, &foodSpawner);
    agentsInGame.push_back(playerAgent);

    // Initialize enemies
    for (int i = 0; i < enemyCount; ++i) {
        Node* enemyStartNode = nodeMap->GetRandomNode(); 

        // Setup decision tree and behavior for each enemy
        ABDecision* rootDecision = SetupEnemyDecisionTree();
        Agent* enemyAgent = new Agent(nodeMap, rootDecision, enemyStartNode, enemySpeed, false, &foodSpawner, playerAgent);
        enemyAgents.push_back(enemyAgent);
        agentsInGame.push_back(enemyAgent);
    }

    foodTracker.Init(playerAgent);
    collisionTracker.Init(playerAgent, enemyAgents);

    musicManager.InitMusicManager(); 
    musicManager.PlayMusic(gameState);

}

    ABDecision* GameManager::SetupEnemyDecisionTree() 
    {
    // Conditions
    float followDistance = 5.0f * nodeMap->GetCellSize();
    DistanceCondition* closeToPlayer = new DistanceCondition(followDistance, true);
    LostTargetCondition* lostTargetCondition = new LostTargetCondition(followDistance);

    // Behaviors
    Behaviour* followBehaviour = new FollowBehaviour();
    Behaviour* wanderBehaviour = new WanderBehaviour();
    Behaviour* goToFoodBehaviour = new GoToFoodBehaviour();

    // Decision nodes
    DecisionBehaviour* followDecision = new DecisionBehaviour(followBehaviour);
    DecisionBehaviour* wanderDecision = new DecisionBehaviour(wanderBehaviour);
    DecisionBehaviour* goToFoodDecision = new DecisionBehaviour(goToFoodBehaviour);

    // Nested decisions
    ABDecision* lostOrWanderDecision = new ABDecision();
    lostOrWanderDecision->condition = lostTargetCondition;
    lostOrWanderDecision->A = goToFoodDecision;
    lostOrWanderDecision->B = wanderDecision;

    // Root decision
    ABDecision* rootDecision = new ABDecision();
    rootDecision->condition = closeToPlayer;
    rootDecision->A = followDecision;
    rootDecision->B = lostOrWanderDecision;

    return rootDecision;
}

void GameManager::Update(float deltaTime)
{
    musicManager.UpdateMusicStream();

    switch (gameState)
    {
    case GameState::MainMenu:
        mainMenu.Update();
        if (mainMenu.GetPlayButton().clicked)
        {
            gameState = GameState::Playing;
            musicManager.PlayMusic(gameState);
        }
        break;
    case GameState::Playing:
        for (Agent* agent : agentsInGame)
        {
            agent->Update(deltaTime);
        }
        foodSpawner.UpdateAllFoods();
        foodTracker.Update();
        scoreTracker.Update();
        playerScore.Update();
        collisionTracker.Update();
        break;
    case GameState::EndGameMenu:
        endGameMenu.Update(deltaTime);
        if (endGameMenu.ShouldExit()) 
        {
            SwitchToMainMenu();
            endGameMenu.Exit();
        }
        break;

    }
}

void GameManager::Draw()
{
    switch (gameState)
    {
    case GameState::MainMenu:
        mainMenu.Draw();
        break;

    case GameState::Playing:
        nodeMap->Draw();
        for (Agent* agent : agentsInGame)
        {
            agent->Draw();
        }
        break;

    case GameState::EndGameMenu:
        endGameMenu.Draw();
        break; 
    }
}

void GameManager::ResetGameState()
{
	scoreTracker.ResetPlayerScore();
	for (Agent* agent : agentsInGame)
	{
		agent->MoveToStartingPosition();
		agent->GetPathAgent()->ClearPath();
		agent->SetWasFollowing(false);
	}
}

void GameManager::SwitchToMainMenu() 
{
    gameState = GameState::MainMenu;
    musicManager.PlayMusic(gameState);
}

void GameManager::SwitchToEndGameMenu()
{
    gameState = GameState::EndGameMenu;
    musicManager.PlayMusic(gameState);
    endGameMenu.SetPlayerScore(playerScore.GetScore());
    mainMenu.SetPlayButton(false);
    ResetGameState();
}