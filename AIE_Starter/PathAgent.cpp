////#include "PathAgent.h"
////
////
////void PathAgent::Update(float deltaTime)
////{
////	if (path.empty()) return;
////
////	float distance = glm::distance(path[currentIndex]->position, position);
////	glm::vec2 dir = glm::normalize(path[currentIndex]->position - position);
////
////	float move = distance - (speed * deltaTime);
////
////	if (move > 0)
////	{
////		position += speed* deltaTime * dir;
////		return;
////	}
////
////	currentIndex++;
////
////	if (currentIndex >= path.size())
////	{
////		//Maybe add back in
////		//position = path[path.size() - 1]->position;
////
////		path.clear();
////
////		return;
////	}
////
////	move *= -1;
////
////	glm::vec2 newDir = glm::normalize(path[currentIndex]->position - path[currentIndex - 1]->position);
////
////	position += move * deltaTime * newDir;
////
////}
////
////void PathAgent::SetDestination(Node* node, NodeMap* nodeMap)
////{
////	path = NodeMap::DijkstrasSearch(currentNode, node, this->GetPosition());
////	//path = NodeMap::DijkstrasSearch(new Node(position.x, position.y), node);
////	path = nodeMap->SmoothPath(path);
////	currentIndex = 0;
////}
////
////void PathAgent::Draw()
////{
////	DrawCircle((int)position.x, (int)position.y, 12, YELLOW);
////}
////
//////void PathAgent::SetNode(Node* node)
//////{
//////	//void SetNode(Node * node) { currentNode = node; position = node->position; }
//////
//////	if (node)
//////	{
//////		currentNode = node;
//////		position = node->position;
//////	}
//////	else
//////	{
//////
//////	}
//////}
//
//
//#pragma once
//#include <glm/fwd.hpp>
//#include <vector>
//#include "Pathfinding.h"
//#include "NodeMap.h"
//
//using namespace AIForGames;
//
//class PathAgent
//{
//
//private:
//	glm::vec2 position;
//	int currentIndex;
//	Node* currentNode;
//	Node* adhocNode;
//	float speed;
//
//public:
//	std::vector<Node*> path;
//	std::vector<Node*> smoothedPath;
//	void Update(float deltaTime);
//	void SetDestination(Node* node, NodeMap* nodeMap);
//	//void SetDestination(Node* node, Agent* agent);
//	void Draw();
//	void SetNode(Node* node)
//	{
//		currentNode = node; position = node->position;
//		//node->UpdateOccupiedStatus(true);
//	}
//
//	void SetCurrentNode(Node* node)
//	{
//		currentNode = node;
//		node->UpdateOccupiedStatus(true);
//	}
//
//	//Attempted fix but noticing weird movement occasionally
//	//void SetNode(Node* node);
//	void SetSpeed(float speed) { this->speed = speed; }
//
//
//	glm::vec2 GetPosition() { return position; }
//};

#include "PathAgent.h"
#include "glm/glm.hpp"


//void PathAgent::Update(float deltaTime)
//{
//	if (smoothedPath.empty()) return;
//
//	float distance = glm::distance(smoothedPath[currentIndex]->position, position);
//	glm::vec2 dir = glm::normalize(smoothedPath[currentIndex]->position - position);
//
//	float move = distance - (speed * deltaTime);
//
//	if (move > 0)
//	{
//		position += speed * deltaTime * dir;
//		return;
//	}
//
//	currentIndex++;
//
//	if (currentIndex >= smoothedPath.size())
//	{
//		//Maybe add back in
//		//position = path[path.size() - 1]->position;
//
//		smoothedPath.clear();
//
//		return;
//	}
//
//	move *= -1;
//
//	glm::vec2 newDir = glm::normalize(smoothedPath[currentIndex]->position - smoothedPath[currentIndex - 1]->position);
//
//	position += move * deltaTime * newDir;
//
//}

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