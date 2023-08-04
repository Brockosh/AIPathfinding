#pragma once
#include "Pathfinding.h"
#include <string>
#include <iostream>
#include <raygui.h>

using namespace AIForGames;

class NodeMap
{
	int width, height;
	float cellSize;
	Node** nodes;
	Node* start;
	Node* end;


	void ConnectWestAndSouth(int x, int y);
	static bool NodeInList(std::vector<Node*> list);

public:
	/*Node* GetStart() const { return start; }
	Node* GetEnd() const { return end; }
	void SetStart(Node* node) { start = node; }
	void SetEnd(Node* node) { end = node; }*/
	void Init(std::vector<std::string> asciiMap, int cellSize);
	Node* GetNode(int x, int y) { return nodes[x + width * y]; }
	void Draw();
	Node* GetClosestNode(glm::vec2 worldPos);
	static std::vector<Node*>DijkstrasSearch(Node* startNode, Node* endNode);
	Node* GetRandomNode();
};

