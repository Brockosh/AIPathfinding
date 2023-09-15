#pragma once
#include "PathAgent.h"
#include "Behaviour.h"
#include "Decision.h"
#include "FoodSpawner.h"
class Agent
{

public:
	Agent();
	Agent(NodeMap* nodeMap, Behaviour* behaviour, Node* startingNode, 
		float speed, bool isPlayer, Color agentColor, FoodSpawner* fs, Agent* targetAgent = nullptr)
	{
		current = behaviour;
		this->nodeMap = nodeMap;
		pathAgent.SetNode(startingNode);
		this->startingPosition = startingNode;
		pathAgent.SetSpeed(speed);
		this->targetAgent = targetAgent;
		color = agentColor;
		this->myFoodSpawner = fs;
		current->Enter(this);
		agentTexture = LoadTexture("MyImages/PlayerBird.png");
		isPlayerAgent = isPlayer;
	}

	Agent(NodeMap* nodeMap, Decision* decisionRoot, Node* startingNode, 
		float speed, bool isPlayer, Color agentColor, FoodSpawner* fs, Agent* targetAgent = nullptr)
	{
		this->decisionRoot = decisionRoot;
		this->nodeMap = nodeMap;
		this->startingPosition = startingNode;
		pathAgent.SetNode(startingNode);
		pathAgent.SetSpeed(speed);
		this->targetAgent = targetAgent;
		color = agentColor;
		this->myFoodSpawner = fs;
		agentTexture = LoadTexture("MyImages/PlayerBird.png");
		isPlayerAgent = isPlayer;
	}

	~Agent() { delete current; delete decisionRoot; UnloadTexture(agentTexture);
	}

	void Reset();
	void MoveToStartingPosition() { this->pathAgent.SetNode(this->startingPosition); };
	void Update(float deltaTime);
	void Draw();
	void GoTo(glm::vec2 pos);

	//void SetNode(Node* node) { pathAgent.SetNode(node); }
	void SetSpeed(float speed) { pathAgent.SetSpeed(speed); }
	std::vector<Node*>  GetPath() { return pathAgent.path; }
	bool PathComplete() { return pathAgent.path.empty(); }
	NodeMap* GetNodeMap() { return this->nodeMap;  }
	PathAgent* GetPathAgent() { return &pathAgent; }
	glm::vec2 GetPosition() { return pathAgent.GetPosition(); }
	void SetTargetAgent(Agent* target) { targetAgent = target; }
	Agent* GetTargetAgent() { return targetAgent; }
	void SetColor(Color color) { this->color = color; }
	bool IsPlayerAgent() { return isPlayerAgent; }
	glm::vec2 GetNearestFoodPosition();
	void SetWasFollowing(bool value) { wasFollowing = value; }
	bool WasFollowing() { return wasFollowing; }

	//Decision* GetDecisionRoot() { return decisionRoot; }

private:
	PathAgent pathAgent;
	Behaviour* current;
	NodeMap* nodeMap;
	Node* startingPosition;
	Color color;
	Agent* targetAgent;
	Decision* decisionRoot;
	Texture2D agentTexture;
	FoodSpawner* myFoodSpawner;
	bool isPlayerAgent;
	bool wasFollowing = false;
};