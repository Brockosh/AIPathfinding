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
		/*if (isPlayer)
		{
			startingPosition = nodeMap->GetRandomNode();
		}*/
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

	~Agent() { delete current; delete decisionRoot; /*UnloadTexture(agentTexture);*/
	}

	void Reset();
	void MoveToStartingPosition() { this->pathAgent.SetNode(this->startingPosition); };
	void Update(float deltaTime);
	void Draw();
	void GoTo(glm::vec2 pos);
	//void UpdateTextures();

	//void SetNode(Node* node) { pathAgent.SetNode(node); }
	void SetSpeed(float speed) { pathAgent.SetSpeed(speed); }
	std::vector<Node*>  GetPath() { return pathAgent.path; }
	bool PathComplete() { return pathAgent.path.empty(); }
	void SetTargetAgent(Agent* target) { targetAgent = target; }
	void SetColor(Color color) { this->color = color; }
	bool IsPlayerAgent() { return isPlayerAgent; }
	void SetWasFollowing(bool value) { wasFollowing = value; }
	bool WasFollowing() { return wasFollowing; }
	bool IsMovingRight();

	NodeMap* GetNodeMap() { return this->nodeMap;  }
	PathAgent* GetPathAgent() { return &pathAgent; }
	glm::vec2 GetPosition() { return pathAgent.GetPosition(); }
	Agent* GetTargetAgent() { return targetAgent; }
	glm::vec2 GetNearestFoodPosition();
	//Decision* GetDecisionRoot() { return decisionRoot; }

	void SetStartingNodeAtMinimumDistance(NodeMap* nodeMap, glm::vec2 referencePosition, float minDistance);

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