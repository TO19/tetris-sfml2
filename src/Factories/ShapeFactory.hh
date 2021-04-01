#ifndef SHAPEFACTORY
#define SHAPEFACTORY

#include "AbstractEntity.hh"
#include "PlayableArea.hh"
#include "ShapeEntity.hh"
#include "AssetsManager.hh"

class ShapeFactory
{
private:
    std::list<BlockEntity *> GenerateBlocks(
        std::vector<sf::Vector2f *> positions,
        std::vector<std::vector<std::pair<int, int>>> coords,
        int size,
        sf::Vector2f pos,
        int type);

public:
    ShapeFactory();
    ~ShapeFactory();
    AbstractEntity *Create(int, const int &size, const sf::Vector2f &playablePos, int);
    AbstractEntity *Unserialize(const std::string &);
};

#endif /* SHAPEFACTORY */
