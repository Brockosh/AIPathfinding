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
	//std::vector<Node*> occupiedNodes;

	Texture2D* cloudTexture;

	void ConnectWestAndSouth(int x, int y);
	static bool NodeInList(std::vector<Node*> list);
	bool IsVisible(Node* start, Node* end);

public:

	void Init(std::vector<std::string> asciiMap, int cellSize);
	Node* GetNode(int x, int y) { return nodes[x + width * y]; }
	void Draw();
	Node* GetClosestNode(glm::vec2 worldPos);
	static std::vector<Node*>DijkstrasSearch(Node* startNode, Node* endNode);
	Node* GetRandomNode();
	Node* GetRandomStartingNode();
	float GetCellSize() { return cellSize; }
	std::vector<Node*> SmoothPath(std::vector<Node*> path);
};

