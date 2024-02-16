#pragma once
#include "Pathfinding.h"
#include <string>
#include <iostream>
#include <raylib.h>

using namespace AIForGames;

class NodeMap
{
	int width, height;
	float cellSize;
	Node** nodes;
	Node* start;
	Node* end;
	
	void ConnectWestAndSouth(int x, int y);

public:
	Texture2D cloudTexture = LoadTexture("MyImages/Cloud.png");
	void Init(std::vector<std::string> asciiMap, int cellSize);
	void Draw();
	float GetCellSize() { return cellSize; }
	static std::vector<Node*>DijkstrasSearch(Node* startNode, Node* endNode, Node* newNode);
	Node* GetNode(int x, int y) { return nodes[x + width * y]; }
	Node* GetClosestNode(glm::vec2 worldPos);
	Node* GetRandomNode();
	Node* GetCenterNode();
};