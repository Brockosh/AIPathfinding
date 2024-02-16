#pragma once
#include "MainMenu.h"
#include "raylib.h"

MainMenu::MainMenu()
    : 
    playButton(Rectangle{ GetScreenWidth() / 2 - 250.0f, GetScreenHeight() / 2 - 100.0f, 
        500.0f, 200.0f }, "Play", IButtonType::Play),
    quitButton(Rectangle{ GetScreenWidth() / 2 - 250.0f, GetScreenHeight() / 2 + 120.0f, 
        500.0f, 200.0f }, "Quit", IButtonType::Quit)
{

    customFont = LoadFont("Fonts/Bubble.ttf");
    Image playerBirdImage = LoadImage("MyImages/Player_01.png");
    Image enemyBirdImage = LoadImage("MyImages/Enemy_02.png");

    // Flip the player bird image horizontally
    ImageFlipHorizontal(&playerBirdImage);

    // Convert the images to textures
    playerBirdTexture = LoadTextureFromImage(playerBirdImage);
    enemyBirdTexture = LoadTextureFromImage(enemyBirdImage);

    // Unload the image data (no longer needed)
    UnloadImage(playerBirdImage);
    UnloadImage(enemyBirdImage);


    playerBirdPosition = { ((float)GetScreenWidth() / 2) + 350, 500};
    enemyBirdPosition = { ((float)GetScreenWidth() / 2) - 660, 500 };
}


void MainMenu::Update() 
{
    playButton.Update();
    quitButton.Update();
}

void MainMenu::Draw()  
{
    // Calculate the width of the game title text and its X position to center it
    int textWidth = MeasureText("Feathered Feast", 150);
    int textX = GetScreenWidth() / 2 - textWidth / 2;

    DrawText("Feathered Feast", textX, GetScreenHeight() / 6, 150, WHITE);

    playButton.Draw();
    quitButton.Draw();


    DrawTextureEx(playerBirdTexture, playerBirdPosition, 0, 0.15f, WHITE);
    DrawTextureEx(enemyBirdTexture, enemyBirdPosition, 0, 0.15f, WHITE); 
}

MainMenu::~MainMenu()
{
    UnloadTexture(playerBirdTexture); 
    UnloadTexture(enemyBirdTexture); 
    UnloadFont(customFont);
}