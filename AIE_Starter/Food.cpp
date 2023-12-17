#include "Food.h"

Food::Food(NodeMap* nm)
{
	this->nodeMap = nm;
    Node* randomNode = nodeMap->GetRandomNode();
	position = glm::vec2(randomNode->position.x, randomNode->position.y);


}


void Food::Update()
{
    if (!isEaten) {
        //DrawCircle(position.x, position.y, 10, WHITE);

		if (&foodTexture != nullptr)
		{
			// Calculate the position to draw the texture
			/*int drawPosX = (int)(x * cellSize);
			int drawPosY = (int)(y * cellSize);*/

			// Calculate scaling factors to fit the texture into the cell
			float scaleWidth = this->nodeMap->GetCellSize() / (float)foodTexture.width;
			float scaleHeight = this->nodeMap->GetCellSize() / (float)foodTexture.height;
			float scale = (scaleWidth < scaleHeight) ? scaleWidth : scaleHeight;

			Vector2 foodPosition = {
				position.x - (foodTexture.width * scale) / 2.0f,
				position.y - (foodTexture.height * scale) / 2.0f
			};

			// Draw the scaled texture
			DrawTextureEx(foodTexture, foodPosition, 0.0f, scale, WHITE);
		}

    }
}