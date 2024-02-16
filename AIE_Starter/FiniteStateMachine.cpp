#include "FiniteStateMachine.h"
#include "State.h"
#include "Condition.h"

FiniteStateMachine::FiniteStateMachine(State* s) : currentState(s), newState(nullptr) 
{
	states.push_back(s);
}


FiniteStateMachine::~FiniteStateMachine()
{
	for (auto s : states)
	{
		delete s;
	}
}

void FiniteStateMachine::Update(Agent* agent, float deltaTime)
{
    newState = nullptr;

    // Iterate through all transitions of the current state
    for (auto t : currentState->GetTransitions())
    {
        // If the transition condition is met, set the new state
        if (t.condition->IsTrue(agent))
        {
            newState = t.targetState;
            break; 
        }
    }

    if (newState != nullptr && newState != currentState)
    {
        currentState->Exit(agent);
        currentState = newState;
        currentState->Enter(agent);
    }

    currentState->Update(agent, deltaTime);
}