#include "PlayerScore.h"
#include <iostream>
#include "raylib.h"
#include <string>

void PlayerScore::Update()
{
	std::string scoreStr = std::to_string(score);
	int textWidth = MeasureText(scoreStr.c_str(), 20);

	DrawText(scoreStr.c_str(), GetScreenWidth() - textWidth - 40,
		10, 50, WHITE);
}