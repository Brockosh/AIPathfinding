#include "FiniteStateMachine.h"
#include "State.h"
#include "Condition.h"

FiniteStateMachine::~FiniteStateMachine()
{
	for (auto s : states)
	{
		delete s;
	}
}

void FiniteStateMachine::Update(Agent* agent, float deltaTime)
{
	//potential issue
	newState = nullptr;

	for (auto t : currentState->GetTransitions())
	{
		if (t.condition->IsTrue(agent))
			newState = t.targetState;
			break;
	}

	if (newState != nullptr && newState != currentState)
	{
		currentState->Exit(agent);
		currentState = newState;
		currentState->Enter(agent);
	}

	currentState->Update(agent, deltaTime);
}
