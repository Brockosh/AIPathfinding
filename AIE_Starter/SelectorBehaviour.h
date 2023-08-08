#pragma once
#include "Behaviour.h"
class SelectorBehaviour : Behaviour
{
private:
	Behaviour* behaviour1;
	Behaviour* behaviour2;

public:
	SelectorBehaviour(Behaviour* b1, Behaviour* b2) : behaviour1(b1), behaviour2(b2) {};
	virtual void Update(Agent* agent, float deltaTime);
};

