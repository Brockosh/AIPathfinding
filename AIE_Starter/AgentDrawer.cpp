#include "AgentDrawer.h"
#include "Agent.h"

void AgentDrawer::Update(float deltaTime)
{
    // Increment the timer by the elapsed time
    wingFlapTimer += deltaTime; 
    // Reset the timer once it exceeds the interval for a wing flap cycle
    if (wingFlapTimer > wingFlapInterval)
    {
        wingFlapTimer -= wingFlapInterval;
    }
}


void AgentDrawer::Draw(Agent& agent)
{
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

    // Calculate the drawing position and scale for the agent's texture
    float scale = 0.03f; 
    Vector2 drawPosition =
    {
        agentPosition.x - (textureToUse.width * scale) / 2.0f, 
        agentPosition.y - (textureToUse.height * scale) / 2.0f
    };

    // Draw the selected texture at the calculated position and scale
    DrawTextureEx(textureToUse, drawPosition, 0.0f, scale, WHITE);
}