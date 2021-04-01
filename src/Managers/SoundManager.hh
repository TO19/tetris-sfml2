#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class SoundManager
{
private:
    sf::SoundBuffer gameOverSoundBuffer;
    sf::Sound gameOverSound;
    sf::Music musicBackground;

public:
    SoundManager();
    void playGameOver();
    void playTetrisMusic();
};