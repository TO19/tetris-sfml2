#include "SoundManager.hh"

SoundManager::SoundManager()
{
    if (!gameOverSoundBuffer.loadFromFile("./Assets/gameover.wav"))
    {
        std::cout << "Game over sound effect not loaded." << std::endl;
    };

    if (!musicBackground.openFromFile("Assets/venom-tetris.ogg"))
    {
        std::cout << "Tetris music not loaded." << std::endl;
    }
}

void SoundManager::playGameOver()
{
    gameOverSound.setBuffer(gameOverSoundBuffer);
    gameOverSound.play();
    std::cout << "Game over launch sound \n";
}

void SoundManager::playTetrisMusic()
{
    musicBackground.setVolume(30);
    musicBackground.setLoop(true);
    musicBackground.play();
}
