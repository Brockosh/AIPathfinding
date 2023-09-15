#include "ScoreTracker.h"

void ScoreTracker::Update()
{
	for (Food* food : foodSpawner->GetActiveFood())
	{
		if (food->GetEatenStatus())
		{
			playerScore->IncreaseScore(1);
		}
	}
}

