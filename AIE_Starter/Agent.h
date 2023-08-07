#pragma once
#include "PathAgent.h"
#include "Behaviour.h"

class Agent
{

public:
	Agent();
	Agent(NodeMap* nodeMap, Behaviour* behaviour, Node* startingNode, float speed, Color agentColor = YELLOW, Agent* targetAgent = nullptr)
	{
		current = behaviour;
		this->nodeMap = nodeMap;
		pathAgent.SetNode(startingNode);
		pathAgent.SetSpeed(speed);
		this->targetAgent = targetAgent;
		color = agentColor;
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
	glm::vec2 GetPosition() { return pathAgent.GetPosition(); }

	void SetTargetAgent(Agent* target) { targetAgent = target; }

	Agent* GetTargetAgent() { return targetAgent; }

private:
	PathAgent pathAgent;
	Behaviour* current;
	NodeMap* nodeMap;
	Color color;
	Agent* targetAgent;
};

