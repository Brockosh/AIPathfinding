#pragma once
#include "PathAgent.h"
#include "Behaviour.h"

class Agent
{

public:
	Agent();
	Agent(NodeMap* nodeMap, Behaviour* behaviour, Node* startingNode, float speed)
	{
		current = behaviour;
		this->nodeMap = nodeMap;
		pathAgent.SetNode(startingNode);
		pathAgent.SetSpeed(speed);
		color = { 255, 255, 0, 255 };
	}
	~Agent() { delete current; }

	void Update(float deltaTime);
	void Draw();
	void GoTo(glm::vec2 pos);

	//void SetNode(Node* node) { pathAgent.SetNode(node); }
	void SetSpeed(float speed) { pathAgent.SetSpeed(speed); }
	std::vector<Node*>  GetPath() { return pathAgent.path; }
	bool PathComplete() { return pathAgent.path.empty(); }

	NodeMap* GetNodeMap() { return this->nodeMap;  }
	PathAgent GetPathAgent() { return this->pathAgent; }

private:
	PathAgent pathAgent;
	Behaviour* current;
	NodeMap* nodeMap;
	Color color;
};

