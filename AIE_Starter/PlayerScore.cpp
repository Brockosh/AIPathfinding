#include "PlayerScore.h"
#include <iostream>
#include "raylib.h"
#include <string>

void PlayerScore::Update()
{
    std::string scoreStr = std::to_string(score);
    std::string ScoreText = "Score: "; // Add a colon and space for formatting
    std::string combinedStr = ScoreText + scoreStr; // Combine the ScoreText and scoreStr

    // Calculate the width of the combined string
    int textWidth = MeasureText(combinedStr.c_str(), 100);

    // Calculate the position to draw the combined string so that it is centered
    int drawX = (GetScreenWidth() - textWidth) / 2;
    int drawY = 1025; 

    // Draw the combined string with the calculated position
    DrawText(combinedStr.c_str(), drawX, drawY, 100, WHITE); 
}