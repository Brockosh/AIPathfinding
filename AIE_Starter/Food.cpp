#include "Food.h"

Food::Food(NodeMap* nm)
{
	this->nodeMap = nm;
    Node* randomNode = nodeMap->GetRandomNode();
	position = glm::vec2(randomNode->position.x, randomNode->position.y);


}


//Food::Food(NodeMap* nm) {
//    this->nodeMap = nm;
//    Node* node = nodeMap->GetRandomNode();
//    if (node) { // Check if the node is not nullptr (which it shouldn't be based on current implementation).
//        position = glm::vec2(node->position.x, node->position.y);
//    }
//    else {
//        // Handle unexpected scenario or add an assertion to crash the program during debugging.
//        std::cerr << "Error: Unexpected null node." << std::endl;
//        // Or: assert(false && "Unexpected null node.");
//    }
//}


void Food::Update()
{
    if (!isEaten) {
        DrawCircle(position.x, position.y, 10, WHITE);
    }
}