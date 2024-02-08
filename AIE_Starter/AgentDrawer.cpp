#include "AgentDrawer.h"
#include "Agent.h"

void AgentDrawer::Update(float deltaTime)
{
    wingFlapTimer += deltaTime;
    if (wingFlapTimer > wingFlapInterval)
    {
        wingFlapTimer -= wingFlapInterval;
    }
}


void AgentDrawer::Draw(Agent& agent) 
{

    //Texture2D& textureToUse = (wingFlapTimer < wingFlapInterval / 2) ? agentTexture1 : agentTexture2;

    glm::vec2 agentPosition = agent.GetPosition();

    
    
        bool movingRight = agent.GetPathAgent()->IsMovingTowardsDestinationRight();

        if (movingRight)
        {
           textureToUse = (wingFlapTimer < wingFlapInterval / 2) ? agentTexture1 : agentTexture2;
        }
        else
        {

            textureToUse = (wingFlapTimer < wingFlapInterval / 2) ? agentTexture3 : agentTexture4;
        }
    


    float scale = 0.03f; 
    Vector2 drawPosition = 
    {
        agentPosition.x - (textureToUse.width * scale) / 2.0f,
        agentPosition.y - (textureToUse.height * scale) / 2.0f
    };

    DrawTextureEx(textureToUse, drawPosition, 0.0f, scale, WHITE);
}