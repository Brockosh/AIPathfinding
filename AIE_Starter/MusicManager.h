#pragma once
#include <raylib.h>
#include "GameState.h"
class MusicManager
{

private:
    Music mainMenuMusic;
    Music playingMusic;
    Music endGameMusic;

public:
       void  InitMusicManager(); 
       void PlayMusic(GameState gameState);
       void UpdateMusicStream();

    ~MusicManager() {
        // Unload music and close audio device
        UnloadMusicStream(mainMenuMusic);
        UnloadMusicStream(playingMusic);
        CloseAudioDevice();
    }

};

