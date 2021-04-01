#include "env.hh"
#include "Menu.hh"
#include "AssetsManager.hh"

Menu::Menu(sf::RenderWindow *windowMenu) : Scene(windowMenu)
{
    AssetsManager::loadTexture("Tetris_back", Tetris_back);
    AssetsManager::loadTexture("Title", Title);
    AssetsManager::loadTexture("New_game", New_game);
    AssetsManager::loadTexture("Leaderboard", Leaderboard);
    AssetsManager::loadTexture("Exit", Exit);

    sf::Texture *tetris_back = AssetsManager::getTexture("Tetris_back");
    sf::Texture *title = AssetsManager::getTexture("Title");
    sf::Texture *newGame = AssetsManager::getTexture("New_game");
    sf::Texture *leaderboard = AssetsManager::getTexture("Leaderboard");
    sf::Texture *exit = AssetsManager::getTexture("Exit");

    this->_spriteBack.setTexture(*tetris_back);
    this->_spriteTitle.setTexture(*title);
    this->_spriteNG.setTexture(*newGame);
    this->_spriteL.setTexture(*leaderboard);
    this->_spriteE.setTexture(*exit);

    this->_spriteBack.setScale(1.3, 2);
    this->_spriteTitle.setScale(0.8, 0.8);
    this->_spriteTitle.setPosition(340, 50);
    this->_spriteNG.setPosition(400, 330);
    this->_spriteL.setPosition(400, 480);
    this->_spriteE.setPosition(400, 600);

    this->_boundNG = _spriteNG.getGlobalBounds();
    this->_boundL = _spriteL.getGlobalBounds();
    this->_boundE = _spriteE.getGlobalBounds();

    this->_window = windowMenu;
}
Menu::~Menu(){};

sf::RenderWindow *Menu::GetWindow()
{
    return this->_window;
}

void Menu::Update()
{
    this->_window->clear();
    this->_window->draw(this->_spriteBack);
    this->_window->draw(this->_spriteTitle);
    this->_window->draw(this->_spriteNG);
    this->_window->draw(this->_spriteL);
    this->_window->draw(this->_spriteE);

    this->_window->display();
}

sf::FloatRect Menu::GetBoundNG()
{
    return _boundNG;
}

sf::FloatRect Menu::GetBoundL()
{
    return _boundL;
}

sf::FloatRect Menu::GetBoundE()
{
    return _boundE;
}