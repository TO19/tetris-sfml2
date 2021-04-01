#include "BlockEntity.hh"
#include "TimeManager.hh"
#include <math.h>

BlockEntity::BlockEntity() {}
BlockEntity::BlockEntity(sf::RectangleShape block)
{
    this->_block = block;
}

void BlockEntity::Draw(sf::RenderWindow *window)
{
    window->draw(GetBlock());
};

void BlockEntity::Update(){};

void BlockEntity::UpdatePosition()
{
    sf::RectangleShape shape = GetBlock();
}

sf::RectangleShape BlockEntity::GetBlock() const
{
    return this->_block;
}

void BlockEntity::SetBlock(sf::RectangleShape block)
{
    this->_block = block;
}

std::vector<std::pair<int, int>> BlockEntity::GetPosList() const
{
    return this->_posList;
}

void BlockEntity::SetPosList(std::vector<std::pair<int, int>> list)
{
    this->_posList = list;
}

void BlockEntity::Turn(int position, bool revert)
{
    sf::RectangleShape rect = GetBlock();
    int sizeX = rect.getSize().x;
    int sizeY = rect.getSize().y;
    int newX;
    int newY;
    if (revert) {
        newX = GetBlock().getPosition().x - (GetPosList().at(position).first * sizeX);
        newY = GetBlock().getPosition().y - (GetPosList().at(position).second * sizeY);
    } else {
        newX = GetBlock().getPosition().x + (GetPosList().at(position).first * sizeX);
        newY = GetBlock().getPosition().y + (GetPosList().at(position).second * sizeY);
    }

    rect.setPosition(newX, newY);
    SetBlock(rect);
};