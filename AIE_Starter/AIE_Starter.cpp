#define RAYGUI_SUPPORT_ICONS
//#include "raygui.h"
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
    int screenWidth = 1600;
    int screenHeight = 1150;

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

    int numberOfEnemies = 7;
    float playerSpeed = 50 * 3.5;
    float enemySpeed = playerSpeed - 20;
    int burgerAmount = 30;
    GameManager gameManager(&nodeMap, numberOfEnemies, playerSpeed, enemySpeed, burgerAmount);


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

        gameManager.Update(deltaTime);

        if (gameManager.IsQuitting()) 
        {
            break; 
        }

        BeginDrawing();
        ClearBackground({ 135, 206, 235 });
        gameManager.Draw();
        EndDrawing();

        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}