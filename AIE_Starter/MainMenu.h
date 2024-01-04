#pragma once
#include "raylib.h"
#include "raygui.h"
#include "Button.h"

class MainMenu {
private:
    Button playButton;
    Button quitButton;

    Texture playerBirdTexture;
    Texture enemyBirdTexture;

    Vector2 playerBirdPosition;
    Vector2 enemyBirdPosition;

    Font customFont;
public:
    MainMenu();
    ~MainMenu();
    Button GetPlayButton() { return playButton; }
    Button GetQuitButton() { return quitButton; }
    void SetPlayButton(bool clickedStatus) { playButton.clicked = clickedStatus; }

    void Update();  
    void Draw();

};



