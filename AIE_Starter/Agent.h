#pragma once
#include "PathAgent.h"
#include "Behaviour.h"
#include "Decision.h"
#include "FoodSpawner.h"
#include "AgentDrawer.h"
class Agent
{
public:
	Agent();
	Agent(NodeMap* nodeMap, Behaviour* behaviour, Node* startingNode, 
		float speed, bool isPlayer, FoodSpawner* fs, Agent* targetAgent = nullptr)
		: agentDrawer(isPlayer)
	{
		current = behaviour;
		this->nodeMap = nodeMap;
		pathAgent.SetNode(startingNode);
		this->startingPosition = startingNode;
		pathAgent.SetSpeed(speed);
		this->targetAgent = targetAgent;
		color = WHITE;
		this->myFoodSpawner = fs;
		current->Enter(this);
		isPlayerAgent = isPlayer;
	}

	Agent(NodeMap* nodeMap, Decision* decisionRoot, 
		float speed, bool isPlayer, FoodSpawner* fs, Agent* targetAgent = nullptr)
		: agentDrawer(isPlayer)
	{
		this->decisionRoot = decisionRoot;
		this->nodeMap = nodeMap;
		pathAgent.SetSpeed(speed);
		this->targetAgent = targetAgent;
		color = WHITE;
		this->myFoodSpawner = fs;
		isPlayerAgent = isPlayer;
	}

	~Agent() { delete current; delete decisionRoot; }

	void Reset();
	void MoveToStartingPosition() { this->pathAgent.SetNode(this->startingPosition); };
	void Update(float deltaTime);
	void Draw();
	void GoTo(glm::vec2 pos);
	void SetStartingNodeAtMinimumDistance(NodeMap* nodeMap, glm::vec2 referencePosition, float minDistance);
	void SetSpeed(float speed) { pathAgent.SetSpeed(speed); }
	void SetTargetAgent(Agent* target) { targetAgent = target; }
	void SetColor(Color color) { this->color = color; }
	void SetWasFollowing(bool value) { wasFollowing = value; }

	bool PathComplete() { return pathAgent.path.empty(); }
	bool IsPlayerAgent() { return isPlayerAgent; }
	bool WasFollowing() { return wasFollowing; }
	bool IsMovingRight();

	std::vector<Node*>  GetPath() { return pathAgent.path; }
	NodeMap* GetNodeMap() { return this->nodeMap;  }
	PathAgent* GetPathAgent() { return &pathAgent; }
	Agent* GetTargetAgent() { return targetAgent; }
	glm::vec2 GetPosition() { return pathAgent.GetPosition(); }
	glm::vec2 GetNearestFoodPosition();

private:
	PathAgent pathAgent;
	Behaviour* current;
	NodeMap* nodeMap;
	Node* startingPosition;
	Color color;
	Agent* targetAgent;
	Decision* decisionRoot;
	AgentDrawer agentDrawer;
	FoodSpawner* myFoodSpawner;
	glm::vec2 previousPosition;
	bool isPlayerAgent;
	bool wasFollowing = false;
};