#define MainMENU

#include <iostream>
#include <SFML/Graphics.hpp>
#include <AssetsManager.hh>
#include "Scene.hh"

class Menu : public Scene
{
private:
    sf::Sprite _spriteBack;
    sf::Sprite _spriteTitle;
    sf::Sprite _spriteNG;
    sf::Sprite _spriteL;
    sf::Sprite _spriteE;
    sf::FloatRect _boundNG;
    sf::FloatRect _boundL;
    sf::FloatRect _boundE;

public:
    Menu(sf::RenderWindow *);
    ~Menu();
    sf::RenderWindow *GetWindow();
    void Update();
    sf::FloatRect GetBoundNG();
    sf::FloatRect GetBoundL();
    sf::FloatRect GetBoundE();
};