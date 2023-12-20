#include "EndGameMenu.h"


EndGameMenu::EndGameMenu() : displayTime(3.0f), elapsedTime(0.0f), playerScore(0) {}

//void EndGameMenu::Start(int score) 
//{
//    playerScore = score;
//    elapsedTime = 0.0f;
//}

void EndGameMenu::Update(float deltaTime) 
{
    elapsedTime += deltaTime;
}

bool EndGameMenu::ShouldExit() 
{
    return elapsedTime >= displayTime;
}


void EndGameMenu::Draw() 
{
    // Display the score centered on the screen
    std::string scoreText = "Score: " + std::to_string(playerScore);
    int fontSize = 300; // Adjust as needed
    int textWidth = MeasureText(scoreText.c_str(), fontSize);
    DrawText(scoreText.c_str(), GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 3, fontSize, WHITE);
}