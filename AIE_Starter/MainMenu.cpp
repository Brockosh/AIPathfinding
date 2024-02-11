#pragma once
#include "MainMenu.h"
#include "raylib.h"
//#include "raygui.h"

MainMenu::MainMenu()
    : 
    playButton(Rectangle{ GetScreenWidth() / 2 - 250.0f, GetScreenHeight() / 2 - 100.0f, 
        500.0f, 200.0f }, "Play", IButtonType::Play),
    quitButton(Rectangle{ GetScreenWidth() / 2 - 250.0f, GetScreenHeight() / 2 + 120.0f, 
        500.0f, 200.0f }, "Quit", IButtonType::Quit)
{
    /*playerBirdTexture = LoadTexture("MyImages/Player_01.png");
    enemyBirdTexture = LoadTexture("MyImages/Player_02.png");*/

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


// Update function to handle menu logic
void MainMenu::Update() 
{
    playButton.Update();
    quitButton.Update();

    //if (quitButton.clicked)
    //{
    //    WindowShouldClose();
    //}
}

// Draw function to handle rendering of the menu
void MainMenu::Draw()  
{

    int textWidth = MeasureText("Feathered Feast", 150);
    int textX = GetScreenWidth() / 2 - textWidth / 2;

    Vector2 textPos = { textX, GetScreenHeight() / 6 };
    //DrawTextEx(customFont, "Feathered Feast", textPos, 150, 100, WHITE);

    DrawText("Feathered Feast", textX, GetScreenHeight() / 6, 150, WHITE);
    playButton.Draw();
    quitButton.Draw();
    //Rectangle insertRec = { 200, 400, -10, 50 };

    DrawTextureEx(playerBirdTexture, playerBirdPosition, 0, 0.15f, WHITE);
    //DrawTextureRec(playerBirdTexture, insertRec, playerBirdPosition, WHITE);
    // Draw the second bird (bottom left, angled up)
    DrawTextureEx(enemyBirdTexture, enemyBirdPosition, 0, 0.15f, WHITE); 
}

MainMenu::~MainMenu()
{
    UnloadTexture(playerBirdTexture); 
    UnloadTexture(enemyBirdTexture); 
    UnloadFont(customFont);
}