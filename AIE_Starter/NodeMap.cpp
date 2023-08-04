#include "NodeMap.h"
#include <iostream>
#include "Pathfinding.h"
#include <algorithm>



void NodeMap::ConnectWestAndSouth(int x, int y)
{
	Node* node = GetNode(x, y);
	if (node != nullptr)
	{
		Node* nodeWest = (x == 0) ? nullptr : GetNode(x - 1, y);

		if (nodeWest != nullptr)
		{
			node->ConnectTo(nodeWest, 1);
			nodeWest->ConnectTo(node, 1);
		}

		Node* nodeSouth = (y == 0) ? nullptr : GetNode(x, y - 1);

		if (nodeSouth != nullptr)
		{

			node->ConnectTo(nodeSouth, 1);
			nodeSouth->ConnectTo(node, 1);
		}


	}

}





void NodeMap::Init(std::vector<std::string> asciiMap, int cellSize)
{
	this->cellSize = cellSize;
	const char emptySquare = '0';

	height = asciiMap.size();
	width = asciiMap[0].size();

	nodes = new Node * [width * height];

	for (int y = 0; y < height; y++)
	{
		std::string& line = asciiMap[y];

		if (line.size() != width)
		{
			std::cout << "Mismatched line #" << y << " in ASCII map (" << line.size() << " instead of " << width << ")" << std::endl;
		}

		for (int x = 0; x < width; x++)
		{
			// get the x-th character, or return an empty node if the string isn't long enough
			char tile = x < line.size() ? line[x] : emptySquare;

			// create a node for anything but a '.' character
			nodes[x + width * y] = tile == emptySquare ? nullptr
			: new Node((float)(x + 0.5f) * cellSize, (float)(y + 0.5f) * cellSize);
		}
	}

	// Connect nodes after they are initialized.
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			ConnectWestAndSouth(x, y);
		}
	}
}

void NodeMap::Draw()
{
	Color cellColor{ 255, 0, 0, 255 };
	Color lineColor{ 255, 0, 0, 255 };

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Node* node = GetNode(x, y);
			if (node == nullptr) 
			{
				DrawRectangle((int)(x * cellSize), (int)(y * cellSize), (int)cellSize - 1, (int)cellSize - 1, cellColor);
				continue;
			}

			for (int i = 0; i < node->connections.size(); i++)
			{
				Node* other = node->connections[i].target;
				DrawLine((x + 0.5f) * cellSize, (y + 0.5) * cellSize, (int)other->position.x, (int)other->position.y, lineColor);
			}
		}
	}
}


bool NodeMap::NodeInList(std::vector<Node*> list)
{

	Node* test;
	if (std::find(list.begin(), list.end(), test) == list.end())
	
	return false;
	return true;
}

Node* NodeMap::GetClosestNode(glm::vec2 worldPos)
{
	int i = (int)(worldPos.x / cellSize);
	if (i < 0 || i >= width) return nullptr;
	int j = (int)(worldPos.y / cellSize);
	if (j < 0 || j >= height) return nullptr;

	Node* node = GetNode(i, j);
	if (node == nullptr) return nullptr; // Return nullptr if the node is non-navigable

	return node;
}


std::vector<Node*> NodeMap::DijkstrasSearch(Node* startNode, Node* endNode)
{
	if (startNode == nullptr || endNode == nullptr)
	{
		std::cout << "Error: Invalid input.";
		return std::vector<Node*>();
	}

	if (startNode == endNode)
	{
		return std::vector<Node*>();
	}

	startNode->gScore = 0;
	startNode->previous = nullptr;

	std::vector<Node*> openList;
	std::vector<Node*> closedList;

	openList.push_back(startNode);

	while (!openList.empty())
	{
		std::sort(openList.begin(), openList.end(), [](Node* a, Node* b) {
			return a->gScore < b->gScore;
			});

		Node* currentNode = openList.front();
		openList.erase(openList.begin());

		if (currentNode == endNode)
		{
			break;
		}

		closedList.push_back(currentNode);

		for (const Edge& edge : currentNode->connections)
		{
			if (std::find(closedList.begin(), closedList.end(), edge.target) == closedList.end())
			{
				float gScore = currentNode->gScore + edge.cost;

				if (std::find(openList.begin(), openList.end(), edge.target) == openList.end())
				{
					edge.target->gScore = gScore;
					edge.target->previous = currentNode;
					openList.push_back(edge.target);
				}
				else if (gScore < edge.target->gScore)
				{
					edge.target->gScore = gScore;
					edge.target->previous = currentNode;
				}
			}
		}
	}

	std::vector<Node*> path;
	Node* currentNode = endNode;

	while (currentNode != nullptr)
	{
		path.insert(path.begin(), currentNode);
		currentNode = currentNode->previous;
	}

	return path;
}

Node* NodeMap::GetRandomNode()
{
	Node* node = nullptr;
	while (node == nullptr)
	{
		int x = rand() % width;
		int y = rand() % height;

		node = GetNode(x, y);
	}
	return node;
}

