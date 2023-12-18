#pragma once
#include "raylib.h"
#include "raygui.h"

class MainMenu {
public:
    MainMenu(int screenWidth, int screenHeight)
        : screenWidth(screenWidth), screenHeight(screenHeight) {}

    int Update();  
    void Draw();

private:
    int screenWidth, screenHeight;
    
};



