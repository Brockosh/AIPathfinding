#include "PathAgent.h"
#include "glm/glm.hpp"


void PathAgent::Update(float deltaTime)
{
	if (path.empty()) return;

	float distance = glm::distance(path[currentIndex]->position, position);
	glm::vec2 dir = glm::normalize(path[currentIndex]->position - position);

	float move = distance - (speed * deltaTime);

	if (move > 0)
	{
		position += speed * deltaTime * dir;
		return;
	}

	currentIndex++;

	if (currentIndex >= path.size())
	{
		//Maybe add back in
		//position = path[path.size() - 1]->position;

		path.clear();

		return;
	}

	move *= -1;

	glm::vec2 newDir = glm::normalize(path[currentIndex]->position - path[currentIndex - 1]->position);

	position += move * deltaTime * newDir;

}

void PathAgent::SetDestination(Node* node, NodeMap* nodeMap)
{
	if (adhocNode != nullptr) delete adhocNode;
	adhocNode = new Node((float)this->GetPosition().x, (float)this->GetPosition().y);
	path = NodeMap::DijkstrasSearch(currentNode, node, adhocNode);
	//path = NodeMap::DijkstrasSearch(new Node(position.x, position.y), adhocNode);
	//smoothedPath = nodeMap->SmoothPath(path);
	currentIndex = 0;
}

void PathAgent::Draw()
{
	DrawCircle((int)position.x, (int)position.y, 12, YELLOW);
}

//void PathAgent::SetNode(Node* node)
//{
//	//void SetNode(Node * node) { currentNode = node; position = node->position; }
//
//	if (node)
//	{
//		currentNode = node;
//		position = node->position;
//	}
//	else
//	{
//
//	}
//}