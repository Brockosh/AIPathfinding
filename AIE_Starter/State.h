#pragma once
#include <vector>

class Condition;
class Behaviour;
class Agent;

class State
{

public:
	struct Transition
	{
		Condition* condition;
		State* targetState;
	};
private:
	std::vector<Behaviour*> behaviours;
	std::vector<Transition> transitions;

public:
	State();
	State(Behaviour* b) { behaviours.push_back(b); }
	~State();
	virtual void Enter(Agent* agent) {};
	virtual void Exit(Agent* agent) {};
	virtual void Update(Agent* agent, float deltaTime);

	std::vector<Transition> GetTransitions() { return transitions; }
	void AddTransition(Condition* c, State* s) { transitions.push_back( { c, s }); }

};

