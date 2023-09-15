#pragma once
#include "Behaviour.h"
class SelectorBehaviour : public Behaviour
{
private:
	Behaviour* behaviour1;
	Behaviour* behaviour2;
	Behaviour* selectedBehaviour;

public:
	SelectorBehaviour(Behaviour* b1, Behaviour* b2) : behaviour1(b1), behaviour2(b2) {};
	~SelectorBehaviour() { delete behaviour1, delete behaviour2; }
	virtual void Update(Agent* agent, float deltaTime);
	void SetBehaviour(Behaviour* b, Agent* agent);
};