#pragma once
#include "Behaviour.h"
#include "glm/glm.hpp"

class FollowBehaviour :
    public Behaviour
{
private:
    glm::vec2 lastTargetPosition;
    virtual void Update(Agent* agent, float deltaTime);

public:
    virtual void Enter(Agent* agent);
};

