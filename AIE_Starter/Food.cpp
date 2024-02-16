#include "Food.h"

Food::Food(NodeMap* nm)
{
	this->nodeMap = nm;
	// Get a random node from the nodeMap and set it as the food's position
    Node* randomNode = nodeMap->GetRandomNode();
	position = glm::vec2(randomNode->position.x, randomNode->position.y);
}


void Food::Update()
{
    // Check if the food has not been eaten
    if (!isEaten) {
        // Ensure the food texture is not a null pointer before proceeding
        if (&foodTexture != nullptr)
        {
            // Calculate the scale for the food texture to match the cell size
            float scaleWidth = this->nodeMap->GetCellSize() / (float)foodTexture.width;
            float scaleHeight = this->nodeMap->GetCellSize() / (float)foodTexture.height;
            // Choose the smaller scale to maintain aspect ratio
            float scale = (scaleWidth < scaleHeight) ? scaleWidth : scaleHeight;

            // Calculate the position to draw the food texture centered on its position
            Vector2 foodPosition = {
                position.x - (foodTexture.width * scale) / 2.0f,
                position.y - (foodTexture.height * scale) / 2.0f
            };

            // Draw the food texture at the calculated position and scale, colored white
            DrawTextureEx(foodTexture, foodPosition, 0.0f, scale, WHITE);
        }
    }
}