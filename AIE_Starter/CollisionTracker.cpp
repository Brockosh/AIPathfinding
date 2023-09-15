#include "CollisionTracker.h"
#include "glm/glm.hpp"
#include "Agent.h"
#include "GameManager.h"

CollisionTracker::CollisionTracker(Agent* player, Agent* e1, Agent* e2, Agent* e3, Agent* e4, GameManager* gm)
    : playerAgent(player), gameManager(gm)
{
    chasingAgents.push_back(e1);
    chasingAgents.push_back(e2);
    chasingAgents.push_back(e3);
    chasingAgents.push_back(e4);
}

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



