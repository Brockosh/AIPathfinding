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
       void InitMusicManager(); 
       void PlayMusic(GameState gameState);
       void UpdateMusicStream();
       void SetVolume(float volume);

    ~MusicManager() {
        UnloadMusicStream(mainMenuMusic);
        UnloadMusicStream(playingMusic);
        CloseAudioDevice();
    }
};