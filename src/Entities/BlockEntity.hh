#ifndef BLOCKENTITY
#define BLOCKENTITY
#include <iostream>
#include "Movable.hh"
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <list>

class BlockEntity : public AbstractEntity
{
private:
    sf::RectangleShape _block;
    std::vector<std::pair<int, int>> _posList;

public:
    BlockEntity();
    BlockEntity(sf::RectangleShape block);

    virtual void UpdatePosition();
    virtual void Draw(sf::RenderWindow *);
    virtual void Update();

    void Turn(int, bool);

    std::vector<std::pair<int, int>> GetPosList() const;
    void SetPosList(std::vector<std::pair<int, int>>);

    sf::RectangleShape GetBlock() const;
    void SetBlock(sf::RectangleShape);
};

#endif /* BLOCKENTITY */
