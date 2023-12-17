#pragma once
#include <raylib.h>

class Agent;

class AgentDrawer
{
public:
    AgentDrawer(bool isPlayer) 
    {
        if (isPlayer)
        {
            agentTexture1 = LoadTexture("MyImages/Player_01.png");
            agentTexture2 = LoadTexture("MyImages/Player_02.png");
        }
        else
        {
            agentTexture1 = LoadTexture("MyImages/Enemy_01.png");
            agentTexture2 = LoadTexture("MyImages/Enemy_02.png");
        }
    }

    ~AgentDrawer() 
    {
        UnloadTexture(agentTexture1);
        UnloadTexture(agentTexture2);
    }

    void Update(float deltaTime);
    void Draw(Agent& agent);

private:
    Texture agentTexture1;
    Texture agentTexture2;
    float wingFlapTimer = 0.0f;
    float wingFlapInterval = 0.5f;
};

