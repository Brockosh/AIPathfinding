#pragma once
class PlayerScore
{
private:
	int score;

public:
	PlayerScore() { score = 0; };
	void IncreaseScore(int increaseAmount) { score += increaseAmount; }
	/*void Draw();*/
	void ResetScore() { score = 0; }
	void Update();

};