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
#include "DistanceCondition.h"
#include "DecisionBehaviour.h"
#include "State.h"
#include "FiniteStateMachine.h"
#include "Decision.h"
#include "ABDecision.h"

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
    /*asciiMap.push_back("000000000000");
    asciiMap.push_back("010111011100");
    asciiMap.push_back("010101110110");
    asciiMap.push_back("010100000000");
    asciiMap.push_back("010111111110");
    asciiMap.push_back("010000001000");
    asciiMap.push_back("011111111110");
    asciiMap.push_back("000000000000");*/

    asciiMap.push_back("00000000000000000000000000000000");
    asciiMap.push_back("01111111111111111111111111111110");
    asciiMap.push_back("01110001111111001111110001111110");
    asciiMap.push_back("01110101001001001010001001000010");
    asciiMap.push_back("01010101111101111010101111010110");
    asciiMap.push_back("01010111001001111111101001010110");
    asciiMap.push_back("01010111011101001010101001010110");
    asciiMap.push_back("01010101001001111010101111010110");
    asciiMap.push_back("01011101111101001111111001010110");
    asciiMap.push_back("01001000001111000010001001000110");
    asciiMap.push_back("01111111111111001111101111111110");
    asciiMap.push_back("01111101001111111010101000000110");
    asciiMap.push_back("01111101000100001010101011111110");
    asciiMap.push_back("01001001011111111010101010000010");
    asciiMap.push_back("01011101010100001111101010111110");
    asciiMap.push_back("01111111011101111000111111111110");
    asciiMap.push_back("01011101010101111111101010111110");
    asciiMap.push_back("01001001010101000001001010000010");
    asciiMap.push_back("01111111111111111111111111111110");
    asciiMap.push_back("00000000000000000000000000000000");


    NodeMap nodeMap;
    int cellSize = 50;
    int agentMoveSpeed = cellSize * 2.5;
    nodeMap.Init(asciiMap, cellSize);

#pragma endregion

    Node* start = nodeMap.GetNode(1, 1);
    //Node* end = nodeMap.GetNode(10, 2);

    //Color pathColor = { 255, 255, 255, 255 };

    Agent myAgent(&nodeMap, new GoToPointBehaviour(), start, agentMoveSpeed); 


    DistanceCondition* closerThan2 = new DistanceCondition(2.0f * nodeMap.GetCellSize(), true);
    DistanceCondition* furtherThan4 = new DistanceCondition(4.0f * nodeMap.GetCellSize(), false);


    State* wanderState = new State(new WanderBehaviour());
    State* followState = new State(new FollowBehaviour());

    wanderState->AddTransition(closerThan2, followState);
    followState->AddTransition(furtherThan4, wanderState);

    FiniteStateMachine* fsm = new FiniteStateMachine(wanderState);
    //fsm->AddState(wanderState);
    fsm->AddState(followState);

    Agent agentFSM(&nodeMap, fsm, nodeMap.GetRandomNode(), agentMoveSpeed / 2, GREEN, &myAgent);


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
        agentFSM.Update(deltaTime);
      

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        myAgent.Draw();
        agentFSM.Draw();
        nodeMap.Draw();

        DrawPath(myAgent.GetPath(), WHITE);
        DrawPath(agentFSM.GetPath(), GREEN);
     


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}