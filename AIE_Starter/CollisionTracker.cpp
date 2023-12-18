#include "CollisionTracker.h"
#include "glm/glm.hpp"
#include "Agent.h"
#include "GameManager.h"

CollisionTracker::CollisionTracker(Agent* player, GameManager* gm)
    : playerAgent(player), gameManager(gm){}


bool CollisionTracker::IsColliding(Agent* player, Agent* enemy)
{
    float distance = glm::distance(player->GetPosition(), enemy->GetPosition());
    
    return distance < 5.0f;
    std::cout << "Collision has Occured;" << std::endl;
}

void CollisionTracker::Update()
{
    for (auto enemy : chasingAgents)
    {
        if (IsColliding(playerAgent, enemy))
        {
            std::cout << "HIT" << std::endl;
            gameManager->ResetGameState();
        }
    }
}

void CollisionTracker::Init(Agent* player, std::vector<Agent*>& enemies)
{
    playerAgent = player;
    chasingAgents = enemies;
}