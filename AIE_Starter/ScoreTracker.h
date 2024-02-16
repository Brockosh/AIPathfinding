#pragma once
#include "FoodSpawner.h";
#include "PlayerScore.h"
class ScoreTracker
{
private:
	FoodSpawner* foodSpawner;
	PlayerScore* playerScore;

public:
	ScoreTracker(FoodSpawner* fs, PlayerScore* ps)
		: foodSpawner(fs), playerScore(ps) {}

	void Update();
	void ResetPlayerScore() { playerScore->ResetScore(); }
};