#pragma once
#include <raylib.h>
#include <iostream>
struct Button 
{
	Rectangle rect; 
	const char* text; 
	bool clicked; 

    Button(Rectangle r, const char* t) : rect(r), text(t), clicked(false) {}

    // Check if the button is clicked
    void Update() 
    {
        if (CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            clicked = true;
            std::cout << "Clicked now true";
        }
    }

    // Render the button
    void Draw() const 
    {

        DrawRectangleRec(rect, clicked ? DARKBLUE : SKYBLUE);
        int fontSize = 150; // You can adjust this font size as needed
        int textWidth = MeasureText(text, fontSize);

        // MeasureText doesn't provide text height directly, so we use a general estimate
        // for most fonts, the height is approximately 1.5 times the font size
        int textHeight = fontSize * 1.6;

        // Calculate the x and y positions to center the text
        float textX = rect.x + (rect.width - textWidth) / 2;
        float textY = rect.y - (rect.height - textHeight) / 2;

        DrawText(text, textX, textY, fontSize, WHITE);

    }

};