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


		Node* nodeSouthWest = (x == 0 || y == 0) ? nullptr : GetNode(x - 1, y - 1);
		if (nodeSouthWest)
		{
			node->ConnectTo(nodeSouthWest, 1.414f); 
			nodeSouthWest->ConnectTo(node, 1.414f);
		}

		Node* nodeSouthEast = (x == width - 1 || y == 0) ? nullptr : GetNode(x + 1, y - 1);
		if (nodeSouthEast)
		{
			node->ConnectTo(nodeSouthEast, 1.414f);
			nodeSouthEast->ConnectTo(node, 1.414f);
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
		//Create a reference called "line" to the current line in the ascii map
		std::string& line = asciiMap[y];

		//Check for current line length not equalling ascii map width
		if (line.size() != width)
		{
			std::cout << "Mismatched line #" << y << " in ASCII map (" << line.size() << " instead of " << width << ")" << std::endl;
		}

		for (int x = 0; x < width; x++)
		{
			// Confirm we are within the bounds of the string "line" and if so, assign the character
			// at that index to "tile"
			char tile = x < line.size() ? line[x] : emptySquare;

			// create a node for anything but a '0' character
			nodes[x + width * y] = tile == emptySquare ? 
			nullptr : new Node((float)(x + 0.5f) * cellSize, (float)(y + 0.5f) * cellSize);
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

	//if (this->cloudTexture == nullptr)
	//{
	//	// Allocate memory for the cloud texture
	//	this->cloudTexture = new Texture2D;

	//	// Load the texture from the file
	//	*cloudTexture = LoadTexture("MyImages/Cloud.png");

	//}
}

void NodeMap::Draw()
{
	Color cellColor{ WHITE };
	Color lineColor{ DARKBLUE };

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Node* node = GetNode(x, y);
			if (node == nullptr)
			{
				if (&cloudTexture != nullptr)
				{
					// Calculate the position to draw the texture
					int drawPosX = (int)(x * cellSize);
					int drawPosY = (int)(y * cellSize);

					// Calculate scaling factors to fit the texture into the cell
					float scaleWidth = cellSize / (float)cloudTexture.width;
					float scaleHeight = cellSize / (float)cloudTexture.height;
					float scale = (scaleWidth < scaleHeight) ? scaleWidth : scaleHeight;

					Vector2 position = {drawPosX, drawPosY};

					// Draw the scaled texture
					DrawTextureEx(cloudTexture, position, 0.0f, scale, WHITE);
				}
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


Node* NodeMap::GetClosestNode(glm::vec2 worldPos)
{
	// Convert the world position's x-coordinate to a column index in the grid.
	int i = (int)(worldPos.x / cellSize);

	// Check if the calculated column index is outside the grid's bounds.
	if (i < 0 || i >= width) return nullptr;

	// Convert the world position's y-coordinate to a row index in the grid,
	int j = (int)(worldPos.y / cellSize);

	// Again, check if the row index is outside the grid's bounds.
	if (j < 0 || j >= height) return nullptr;

	// Retrieve and return the node at that grid position.
	return GetNode(i, j);
}


// Dijkstra's algorithm for finding the shortest path between nodes in a graph.
std::vector<Node*> NodeMap::DijkstrasSearch(Node* startNode, Node* endNode, Node* adhocNode)
{
	// Check if the start or end node is null, and if so, return an empty vector.
	if (startNode == nullptr || endNode == nullptr)
	{
		std::cout << "Error: Invalid input.";
		return std::vector<Node*>();
	}

	// If the start and end nodes are the same, return an empty path.
	if (startNode == endNode)
	{
		return std::vector<Node*>();
	}

	// Initialize the starting node's pathfinding values.
	startNode->gScore = 0;
	startNode->previous = nullptr;

	// Create open and closed lists for the nodes to be explored and those already explored.
	std::vector<Node*> openList;
	std::vector<Node*> closedList;

	// Add the starting node to the open list to begin the search.
	openList.push_back(startNode);

	// Continue the search until there are no nodes left to explore.
	while (!openList.empty())
	{
		// Sort the open list by the gScore of the nodes, which represents the shortest path currently known.
		// Lambda compares node g scores and returns bool based on lower score
		std::sort(openList.begin(), openList.end(), [](Node* a, Node* b) 
			{
				return a->gScore < b->gScore;
			});

		// Take the node with the lowest gScore from the open list.
		Node* currentNode = openList.front();
		openList.erase(openList.begin());

		// If the current node is the end node, break out of the loop as the path is found.
		if (currentNode == endNode)
		{
			break;
		}

		// Add the current node to the closed list, indicating it has been explored.
		closedList.push_back(currentNode);

		// Explore all connections (edges) from the current node.
		for (const Edge& edge : currentNode->connections)
		{
			// Skip if the target node of the edge is already in the closed list.
			if (std::find(closedList.begin(), closedList.end(), edge.target) == closedList.end())
			{
				float gScore = currentNode->gScore + edge.cost;

				// If the target node is not in the open list, add it and update its pathfinding values.
				if (std::find(openList.begin(), openList.end(), edge.target) == openList.end())
				{
					edge.target->gScore = gScore;
					edge.target->previous = currentNode;
					openList.push_back(edge.target);
				}
				// If it is in the open list but the new path is shorter, update the target node's pathfinding values.
				else if (gScore < edge.target->gScore)
				{
					edge.target->gScore = gScore;
					edge.target->previous = currentNode;
				}
			}
		}
	}

	// Create a vector to store the path from the end node to the start node.
	std::vector<Node*> path;

	Node* currentNode = endNode;

	// Backtrack from the end node to the start node using the 'previous' pointers.
	while (currentNode != nullptr)
	{
		path.insert(path.begin(), currentNode);
		currentNode = currentNode->previous;
	}

	// Add a connection to the adhoc node from the second node in the path.
	adhocNode->ConnectTo(path[1], 0.25);
	// Replace the first node in the path with the adhoc node.
	path.at(0) = adhocNode;

	// Return the calculated path.
	return path;
}

Node* NodeMap::GetCenterNode()
{
	// Calculate center position in terms of grid coordinates
	int centerX = width / 2;
	int centerY = height / 2;

	// Retrieve and return the node at the center
	return GetNode(centerX, centerY);
}

Node* NodeMap::GetRandomNode()
{
	Node* node = nullptr;
	while (node == nullptr)
	{
		//Use modulus with width and height to keep return values constrained to W-1 and H-1
		int x = rand() % width;
		int y = rand() % height;

		node = GetNode(x, y);
		if (node == nullptr)
		{
			std::cerr << "Error: Random Node at (" << x << "," << y << ") is null!" << std::endl;
		}
	}
	return node;
}