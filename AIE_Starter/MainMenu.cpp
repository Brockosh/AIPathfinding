#pragma once
#include "MainMenu.h"
#include "raylib.h"
#include "raygui.h"


//MainMenu::MainMenu() :
//    playButton({ GetScreenWidth() / 2 - 250, GetScreenHeight() / 2 - 100, 500, 200 }, "Play"),
//    quitButton({ GetScreenWidth() / 2 - 250, GetScreenHeight() / 2 + 120, 500, 200 }, "Quit") {}


MainMenu::MainMenu()
    : 
    playButton(Rectangle{ GetScreenWidth() / 2 - 250.0f, GetScreenHeight() / 2 - 100.0f, 500.0f, 200.0f }, "Play"),
    quitButton(Rectangle{ GetScreenWidth() / 2 - 250.0f, GetScreenHeight() / 2 + 120.0f, 500.0f, 200.0f }, "Quit")
{
}


// Update function to handle menu logic
void MainMenu::Update() 
{
    playButton.Update();
    quitButton.Update();
}

// Draw function to handle rendering of the menu
void MainMenu::Draw()  
{

    int textWidth = MeasureText("Feathered Feast", 150);
    int textX = GetScreenWidth() / 2 - textWidth / 2;


    DrawText("Feathered Feast", textX, GetScreenHeight() / 4, 150, WHITE);

    playButton.Draw();
    quitButton.Draw();


}