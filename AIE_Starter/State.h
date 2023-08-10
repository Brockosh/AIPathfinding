#pragma once
#include <vector>
#include "Behaviour.h"
class State
{
private:
	std::vector<Behaviour*> behaviours;

public:
	State();
	~State();
	virtual void Update(Agent* agent, float deltaTime);

};

