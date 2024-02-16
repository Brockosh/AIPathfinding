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
        // Draw the button rectangle with different color if clicked
        DrawRectangleRec(rect, clicked ? DARKBLUE : SKYBLUE);

        // Calculate the font size and text width
        int fontSize = 150;
        int textWidth = MeasureText(text, fontSize);

        // Calculate the text height (approximately 1.5 times the font size)
        int textHeight = fontSize * 1.6;

        // Calculate the x and y positions to center the text
        float textX = rect.x + (rect.width - textWidth) / 2;
        float textY = rect.y - (rect.height - textHeight) / 2;

        // Draw the button text
        DrawText(text, textX, textY, fontSize, WHITE);
    }
};