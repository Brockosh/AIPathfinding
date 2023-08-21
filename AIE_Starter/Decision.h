#pragma once

class Agent {};
class Decision
{
public:
	virtual void MakeDecision(Agent* agent, float deltaTime) = 0;
};

