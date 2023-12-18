#pragma once
#include "raylib.h"
#include <string>

class EndGameMenu {
private:
    float displayTime;
    float elapsedTime;
    int playerScore;

public:
    EndGameMenu();
    /*void Start(int Score);*/
    void Update(float deltaTime);
    bool ShouldExit();
    void Exit() { elapsedTime = 0; }
    void Draw();
    void SetPlayerScore(int score) {
        playerScore = score;
    }

};
