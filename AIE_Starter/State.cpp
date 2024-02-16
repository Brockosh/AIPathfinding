#include "State.h"
#include "Behaviour.h"

State::State()
{
}

State::~State()
{
	for (Behaviour* b : behaviours)
	{
		delete b;
	}
	for (auto t : transitions)
	{
		delete t.condition;
	}
}


void State::Update(Agent* agent, float deltaTime)
{
	for (auto b : behaviours)
	{
		b->Update(agent, deltaTime);
	}
}