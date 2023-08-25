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
        DrawCircle(position.x, position.y, 10, WHITE);
    }
}