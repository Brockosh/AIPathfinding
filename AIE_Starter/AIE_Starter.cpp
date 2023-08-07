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
    int screenWidth =1080;
    int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

#pragma region Map


    std::vector<std::string> asciiMap;
    asciiMap.push_back("000000000000");
    asciiMap.push_back("010111011100");
    asciiMap.push_back("010101110110");
    asciiMap.push_back("010100000000");
    asciiMap.push_back("010111111110");
    asciiMap.push_back("010000001000");
    asciiMap.push_back("011111111110");
    asciiMap.push_back("000000000000");



    NodeMap nodeMap;
    int cellSize = 85;
    int agentMoveSpeed = cellSize * 2.5;
    nodeMap.Init(asciiMap, cellSize);

#pragma endregion

    Node* start = nodeMap.GetNode(1, 1);
    Node* end = nodeMap.GetNode(10, 2);

    Color pathColor = { 255, 255, 255, 255 };


    Agent agent1(&nodeMap, new GoToPointBehaviour(), start, agentMoveSpeed); 
    Agent agent2(&nodeMap, new WanderBehaviour(), nodeMap.GetRandomNode(), agentMoveSpeed + 50, BLUE);
    Agent agent3(&nodeMap, new FollowBehaviour(), nodeMap.GetRandomNode(), agentMoveSpeed - 40, GREEN, &agent1);

    agent3.SetTargetAgent(&agent1);

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
        agent1.Update(deltaTime);
        agent2.Update(deltaTime);
        agent3.Update(deltaTime);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        agent1.Draw();
        agent2.Draw();
        agent3.Draw();
        nodeMap.Draw();

        DrawPath(agent1.GetPath(), pathColor);
        DrawPath(agent2.GetPath(), BLUE);
        DrawPath(agent3.GetPath(), GREEN);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}