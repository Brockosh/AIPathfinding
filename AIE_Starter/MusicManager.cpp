#include "MusicManager.h"
#include <iostream>

void MusicManager::InitMusicManager()
{

    InitAudioDevice();
	mainMenuMusic = LoadMusicStream("Music/Song1.mp3");
	playingMusic = LoadMusicStream("Music/Song2.mp3");
	endGameMusic = LoadMusicStream("Music/EndSound.mp3");
}



void MusicManager::PlayMusic(GameState gameState) 
{
    std::cout << "Play music called";
    StopMusicStream(mainMenuMusic);
    StopMusicStream(playingMusic);
    StopMusicStream(endGameMusic);

    // Play the music for the current game state
    switch (gameState) 
    {
    case GameState::MainMenu:
        PlayMusicStream(mainMenuMusic);
        SetMusicVolume(mainMenuMusic, 1);
        std::cout << "Play music Main Menu called";
        std::cout << "Song length = " << GetMusicTimeLength(mainMenuMusic);
        break;
    case GameState::Playing:
        PlayMusicStream(playingMusic);
        std::cout << "Play music playing scene called";
        break;
    case GameState::EndGameMenu:
        PlayMusicStream(endGameMusic);
        break;
    }
}

void MusicManager::UpdateMusicStream() 
{
    // Update all music streams
    ::UpdateMusicStream(mainMenuMusic);
    ::UpdateMusicStream(playingMusic);
    ::UpdateMusicStream(endGameMusic);
}