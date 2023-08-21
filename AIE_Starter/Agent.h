#pragma once
#include "PathAgent.h"
#include "Behaviour.h"
#include "Decision.h"

class Agent
{

public:
	Agent();
	/*Agent(NodeMap* nodeMap, Behaviour* behaviour, Node* startingNode, float speed, Color agentColor = YELLOW, Agent* targetAgent = nullptr)
	{
		current = behaviour;
		this->nodeMap = nodeMap;
		pathAgent.SetNode(startingNode);
		pathAgent.SetSpeed(speed);
		this->targetAgent = targetAgent;
		color = agentColor;
		current->Enter(this);
	}*/

	Agent(NodeMap* nodeMap, Decision* decisionRoot, Node* startingNode, float speed, Color agentColor = YELLOW, Agent* targetAgent = nullptr)
	{
		this->decisionRoot = decisionRoot;
		this->nodeMap = nodeMap;
		pathAgent.SetNode(startingNode);
		pathAgent.SetSpeed(speed);
		this->targetAgent = targetAgent;
		color = agentColor;
		// Initialization or entry calls for behaviours would now be in your decision tree structure
	}

	//~Agent() { delete current; }

	~Agent() { delete decisionRoot; }


	//My additions
	void Reset();


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

	void SetColor(Color color) { this->color = color; }

	Decision* GetDecisionRoot() { return decisionRoot; }

private:
	PathAgent pathAgent;
	Behaviour* current;
	NodeMap* nodeMap;
	Color color;
	Agent* targetAgent;
	Decision* decisionRoot;
};

