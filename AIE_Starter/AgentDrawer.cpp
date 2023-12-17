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


void AgentDrawer::Draw(Agent& agent) {
    // Determine which texture to use based on the timer
    //If the timer is less than half the interval, use texture 1
    Texture2D& textureToUse = (wingFlapTimer < wingFlapInterval / 2) ? agentTexture1 : agentTexture2;

    // Assuming Agent class has a method to get its position
    glm::vec2 agentPosition = agent.GetPosition();

    // Calculate the position to draw the texture
    // Adjust these calculations based on how you want the texture to be positioned relative to the agent
    float scale = 0.03f; // Example scale, adjust as needed
    Vector2 drawPosition = 
    {
        agentPosition.x - (textureToUse.width * scale) / 2.0f,
        agentPosition.y - (textureToUse.height * scale) / 2.0f
    };

    // Draw the texture
    DrawTextureEx(textureToUse, drawPosition, 0.0f, scale, WHITE);
}