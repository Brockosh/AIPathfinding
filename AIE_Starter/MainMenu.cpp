#include "MainMenu.h"

int MainMenu::Update() {
    // Cast screenWidth and screenHeight to float for GUI element positioning
    float buttonWidth = 100.0f;
    float buttonHeight = 40.0f;

    Rectangle playButton = 
    {
        static_cast<float>(screenWidth) / 2 - buttonWidth / 2,
        static_cast<float>(screenHeight) / 2 - buttonHeight / 2,
        buttonWidth,
        buttonHeight
    };

    Rectangle quitButton = 
    {
        static_cast<float>(screenWidth) / 2 - buttonWidth / 2,
        static_cast<float>(screenHeight) / 2 + 30.0f,
        buttonWidth,
        buttonHeight
    };

    /*if (GuiButton(playButton, "Play")) 
    {
        return 1;
    }

    if (GuiButton(quitButton, "Quit")) 
    {
        return 2;
    }*/

    return 0;
}

void MainMenu::Draw() {
    // Draw the menu title
    DrawText("Feathered Feast", screenWidth / 2 - MeasureText("Feathered Feast", 20) / 2, screenHeight / 4, 20, BLACK);

    // Note: Buttons are drawn in Update method
}