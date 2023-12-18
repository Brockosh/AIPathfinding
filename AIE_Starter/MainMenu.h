#pragma once
#include "raylib.h"
#include "raygui.h"
#include "Button.h"

class MainMenu {
private:
    Button playButton;
    Button quitButton;



public:
    MainMenu();
    Button GetPlayButton() { return playButton; }
    void SetPlayButton(bool clickedStatus) { playButton.clicked = clickedStatus; }

    void Update();  
    void Draw();

    
};



