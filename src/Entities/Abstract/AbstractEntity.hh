#ifndef ABSTRACTENTITY
#define ABSTRACTENTITY
#include <iostream>
#include <SFML/Graphics.hpp>

class AbstractEntity
{
public:
    AbstractEntity();
    virtual ~AbstractEntity();
    virtual void Draw(sf::RenderWindow *) = 0;
    virtual void Update() = 0;
};

#endif /* ABSTRACTENTITY */
