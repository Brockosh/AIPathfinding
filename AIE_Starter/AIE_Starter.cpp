#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "raylib.h"
#include "Pathfinding.h"
#include <string>
#include "NodeMap.h"
#include "PathAgent.h"
#include "Agent.h"
#include "GoToPointBehaviour.h"
#include "WanderBehaviour.h"
#include "FollowBehaviour.h"
#include "SelectorBehaviour.h"
#include "GoToFoodBehaviour.h"
#include "DistanceCondition.h"
#include "LostTargetCondition.h"
#include "DecisionBehaviour.h"
#include "State.h"
#include "FiniteStateMachine.h"
#include "Decision.h"
#include "ABDecision.h"
#include "Food.h"
#include "FoodSpawner.h"
#include "FoodTracker.h"
#include "PlayerScore.h"
#include "ScoreTracker.h"
#include "CollisionTracker.h"
#include "GameManager.h"

using namespace AIForGames;

static void DrawPath(const std::vector<Node*>& path, Color lineColor)
{
    if (path.size() < 2) return;

    for (size_t i = 0; i < path.size() - 1; i++)
    {
        Vector2 start = { path[i]->position.x, path[i]->position.y };
        Vector2 end = { path[i + 1]->position.x, path[i + 1]->position.y };

        DrawLineEx(start, end, 2.0f, lineColor);
    }
}


int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1920;
    int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "AI Pathfinding");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

#pragma region Map


    std::vector<std::string> asciiMap;

    asciiMap.push_back("00000000000000000000000000000000");
    asciiMap.push_back("01111111111111111111111111111110");
    asciiMap.push_back("01110101111111001111111001111110");
    asciiMap.push_back("01110101001001001010001001000010");
    asciiMap.push_back("01010101111101111010101111010110");
    asciiMap.push_back("01010111001001111111101001010110");
    asciiMap.push_back("01010111011101001010101001110110");
    asciiMap.push_back("01010101001001111010101111010110");
    asciiMap.push_back("01011101111101001111111001010110");
    asciiMap.push_back("01001000001111000010001001010110");
    asciiMap.push_back("01111111111111001111101111111110");
    asciiMap.push_back("01111101001111111010101000000110");
    asciiMap.push_back("01111101000100001010101011111110");
    asciiMap.push_back("01001001011111111010101010010010");
    asciiMap.push_back("01011101010100001111101010111110");
    asciiMap.push_back("01111111011101111000111111111110");
    asciiMap.push_back("01011101010101111111101010111110");
    asciiMap.push_back("01001001010101000001001010000010");
    asciiMap.push_back("01111111111111111111111111111110");
    asciiMap.push_back("00000000000000000000000000000000");


    NodeMap nodeMap;
    int cellSize = 50;
    int agentMoveSpeed = cellSize * 3.5;
    nodeMap.Init(asciiMap, cellSize);

#pragma endregion

    int middleRow = asciiMap.size() / 2;
    int middleColumn = asciiMap[0].length() / 2;
    Node* start = nodeMap.GetNode(middleColumn, middleRow);

    FoodSpawner foodSpawner(&nodeMap, 8);
    Agent myAgent(&nodeMap, new GoToPointBehaviour(), start, agentMoveSpeed, true, YELLOW, &foodSpawner);
    FoodTracker foodTracker(&myAgent, &foodSpawner, &nodeMap);
#pragma region DecisionTree
    //Set up conditions
    DistanceCondition* closerThan5 = new DistanceCondition(5.0f * nodeMap.GetCellSize(), true);
    DistanceCondition* furtherThan4 = new DistanceCondition(4.0f * nodeMap.GetCellSize(), false);
    LostTargetCondition* lostTargetCondition = new LostTargetCondition(5.0f * nodeMap.GetCellSize());

    //Set up behaviours for tree 1
    DecisionBehaviour* followDecision1 = new DecisionBehaviour(new FollowBehaviour());
    DecisionBehaviour* wanderDecision1 = new DecisionBehaviour(new WanderBehaviour());
    DecisionBehaviour* goToFoodFoodDecision1 = new DecisionBehaviour(new GoToFoodBehaviour());

    ABDecision* lostOrWanderDecision1 = new ABDecision();
    lostOrWanderDecision1->condition = lostTargetCondition;
    lostOrWanderDecision1->A = goToFoodFoodDecision1;
    lostOrWanderDecision1->B = wanderDecision1;

    //Set up behaviours for tree 2
    DecisionBehaviour* followDecision2 = new DecisionBehaviour(new FollowBehaviour());
    DecisionBehaviour* wanderDecision2 = new DecisionBehaviour(new WanderBehaviour());
    DecisionBehaviour* goToFoodFoodDecision2 = new DecisionBehaviour(new GoToFoodBehaviour());

    ABDecision* lostOrWanderDecision2 = new ABDecision();
    lostOrWanderDecision2->condition = lostTargetCondition;
    lostOrWanderDecision2->A = goToFoodFoodDecision2;
    lostOrWanderDecision2->B = wanderDecision2;

    //Set up behaviours for tree 3
    DecisionBehaviour* followDecision3 = new DecisionBehaviour(new FollowBehaviour());
    DecisionBehaviour* wanderDecision3 = new DecisionBehaviour(new WanderBehaviour());
    DecisionBehaviour* goToFoodFoodDecision3 = new DecisionBehaviour(new GoToFoodBehaviour());

    ABDecision* lostOrWanderDecision3 = new ABDecision();
    lostOrWanderDecision3->condition = lostTargetCondition;
    lostOrWanderDecision3->A = goToFoodFoodDecision3;
    lostOrWanderDecision3->B = wanderDecision3;

    //Set up behaviours for tree 4
    DecisionBehaviour* followDecision4 = new DecisionBehaviour(new FollowBehaviour());
    DecisionBehaviour* wanderDecision4 = new DecisionBehaviour(new WanderBehaviour());
    DecisionBehaviour* goToFoodFoodDecision4 = new DecisionBehaviour(new GoToFoodBehaviour());

    ABDecision* lostOrWanderDecision4 = new ABDecision();
    lostOrWanderDecision4->condition = lostTargetCondition;
    lostOrWanderDecision4->A = goToFoodFoodDecision4;
    lostOrWanderDecision4->B = wanderDecision4;

    //tree 1
    ABDecision* rootDecision1 = new ABDecision();
    rootDecision1->condition = closerThan5;
    rootDecision1->A = followDecision1;  
    rootDecision1->B = lostOrWanderDecision1;

    //tree 2
    ABDecision* rootDecision2 = new ABDecision();
    rootDecision2->condition = closerThan5;
    rootDecision2->A = followDecision2; 
    rootDecision2->B = lostOrWanderDecision2;

    //tree 3
    ABDecision* rootDecision3 = new ABDecision();
    rootDecision3->condition = closerThan5;
    rootDecision3->A = followDecision3; 
    rootDecision3->B = lostOrWanderDecision3;

    //tree 4
    ABDecision* rootDecision4 = new ABDecision();
    rootDecision4->condition = closerThan5;
    rootDecision4->A = followDecision4;
    rootDecision4->B = lostOrWanderDecision4;

#pragma endregion

#pragma region SetUpStartingPosition
    Node* node1 = nodeMap.GetNode(1, 1);
    Node* node2 = nodeMap.GetNode(1, 18);
    Node* node3 = nodeMap.GetNode(30, 1);
    Node* node4 = nodeMap.GetNode(30, 18);
#pragma endregion

#pragma region AgentSetup
    Agent agent1(&nodeMap, rootDecision1, node1, agentMoveSpeed - 20, false, WHITE, &foodSpawner, &myAgent);
    Agent agent2(&nodeMap, rootDecision2, node2, agentMoveSpeed - 20, false, BLUE, &foodSpawner, &myAgent);
    Agent agent3(&nodeMap, rootDecision3, node3, agentMoveSpeed - 20, false, ORANGE, &foodSpawner, &myAgent);
    Agent agent4(&nodeMap, rootDecision4, node4, agentMoveSpeed - 20, false, PURPLE, &foodSpawner, &myAgent);
#pragma endregion

    PlayerScore playerScore;
    ScoreTracker scoreTracker(&foodSpawner, &playerScore);
    GameManager gameManager(&myAgent, &agent1, &agent2, &agent3, &agent4, &scoreTracker);
    CollisionTracker collisionTracker(&myAgent, &agent1, &agent2, &agent3, &agent4, &gameManager);

    //////////////////////////

    float time = (float)GetTime();
    float deltaTime;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //DeltaTime Calculations
        //----------------------------------------------------------------------------------
        float fTime = (float)GetTime();
        deltaTime = fTime - time;
        time = fTime;

        // UPDATE
        //----------------------------------------------------------------------------------
        myAgent.Update(deltaTime);
        rootDecision1->MakeDecision(&agent1, deltaTime);
        agent1.Update(deltaTime);
        rootDecision2->MakeDecision(&agent2, deltaTime);
        agent2.Update(deltaTime);
        rootDecision3->MakeDecision(&agent3, deltaTime);
        agent3.Update(deltaTime);
        rootDecision4->MakeDecision(&agent4, deltaTime);
        agent4.Update(deltaTime);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground({ 135, 206, 235 });

        myAgent.Draw();
        agent1.Draw();
        agent2.Draw();
        agent3.Draw();
        agent4.Draw();
        nodeMap.Draw();

        foodSpawner.UpdateAllFoods();
        foodTracker.Update();
        scoreTracker.Update();
        playerScore.Update();
        collisionTracker.Update();

        /*DrawPath(myAgent.GetPath(), WHITE);
        DrawPath(agent1.GetPath(), YELLOW);
        DrawPath(agent2.GetPath(), BLUE);
        DrawPath(agent3.GetPath(), ORANGE);
        DrawPath(agent4.GetPath(), PURPLE);*/

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}