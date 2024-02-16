#include "MusicManager.h"
#include <iostream>

void MusicManager::InitMusicManager()
{
    InitAudioDevice();
	mainMenuMusic = LoadMusicStream("Music/Song1.mp3");
	playingMusic = LoadMusicStream("Music/Song2.mp3");
	endGameMusic = LoadMusicStream("Music/EndSound.mp3");
    SetVolume(0.3f);
}

void MusicManager::PlayMusic(GameState gameState) 
{
    StopMusicStream(mainMenuMusic);
    StopMusicStream(playingMusic);
    StopMusicStream(endGameMusic);

    // Play the music for the current game state
    switch (gameState) 
    {
    case GameState::MainMenu:
        PlayMusicStream(mainMenuMusic);
        break;
    case GameState::Playing:
        PlayMusicStream(playingMusic);
        break;
    case GameState::EndGameMenu:
        PlayMusicStream(endGameMusic);
        break;
    }
}

void MusicManager::SetVolume(float volume)
{
    SetMusicVolume(mainMenuMusic, volume);
    SetMusicVolume(playingMusic, volume);
    SetMusicVolume(endGameMusic, volume);
}

void MusicManager::UpdateMusicStream() 
{
    ::UpdateMusicStream(mainMenuMusic);
    ::UpdateMusicStream(playingMusic);
    ::UpdateMusicStream(endGameMusic);
}