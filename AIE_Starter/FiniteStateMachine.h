#pragma once
#include "Behaviour.h"
#include <vector>

class State;

class FiniteStateMachine :
    public Behaviour
{
private:
    std::vector<State*> states;

    State* currentState;
    State* newState;

public:
    FiniteStateMachine(State* s);
    //FiniteStateMachine(State* s) : currentState(s), newState(nullptr) {}
    virtual ~FiniteStateMachine();
    void Update(Agent* agent, float deltaTime);

    void AddState(State* s) { states.push_back(s); }
};

