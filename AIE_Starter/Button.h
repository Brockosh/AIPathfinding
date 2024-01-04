#pragma once
#include <raylib.h>
#include <iostream>
#include "IButtonType.h"


struct Button 
{
	Rectangle rect; 
	const char* text; 
	bool clicked; 
    IButtonType buttonType;

    Button(Rectangle r, const char* t, IButtonType bt) : rect(r), text(t), buttonType(bt), clicked(false) {}

    // Check if the button is clicked
    void Update() 
    {
        if (CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            clicked = true;
            std::cout << "Clicked now true";
        }
    }

    void Draw() const 
    {

        DrawRectangleRec(rect, clicked ? DARKBLUE : SKYBLUE);
        int fontSize = 150; 
        int textWidth = MeasureText(text, fontSize);

        // for most fonts, the height is approximately 1.5 times the font size
        int textHeight = fontSize * 1.6;

        // Calculate the x and y positions to center the text
        float textX = rect.x + (rect.width - textWidth) / 2;
        float textY = rect.y - (rect.height - textHeight) / 2;

        DrawText(text, textX, textY, fontSize, WHITE);
    }
};