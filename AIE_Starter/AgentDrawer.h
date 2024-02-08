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

            Image playerBirdImage = LoadImage("MyImages/Player_01.png");
            Image playerBirdImage2 = LoadImage("MyImages/Player_02.png");
            ImageFlipHorizontal(&playerBirdImage);
            ImageFlipHorizontal(&playerBirdImage2);

            agentTexture3 = LoadTextureFromImage(playerBirdImage);
            agentTexture4 = LoadTextureFromImage(playerBirdImage2);
        }
        else
        {
            agentTexture1 = LoadTexture("MyImages/Enemy_01.png");
            agentTexture2 = LoadTexture("MyImages/Enemy_02.png");

            Image enemyBirdImage = LoadImage("MyImages/Enemy_01.png");
            Image enemyBirdImage2 = LoadImage("MyImages/Enemy_02.png");

            ImageFlipHorizontal(&enemyBirdImage);
            ImageFlipHorizontal(&enemyBirdImage2);
                
            agentTexture3 = LoadTextureFromImage(enemyBirdImage);
            agentTexture4 = LoadTextureFromImage(enemyBirdImage2);
        }
    }

    ~AgentDrawer() 
    {
        UnloadTexture(agentTexture1);
        UnloadTexture(agentTexture2);
        UnloadTexture(agentTexture3);
        UnloadTexture(agentTexture4);
    }

    void Update(float deltaTime);
    void Draw(Agent& agent);

    Texture textureToUse;
private:
    Texture agentTexture1;
    Texture agentTexture2;
    Texture agentTexture3;
    Texture agentTexture4;


    float wingFlapTimer = 0.0f;
    float wingFlapInterval = 0.5f;
};

