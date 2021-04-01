
#include "ShapeFactory.hh"
#include <math.h>
#include "TimeManager.hh"
#include "../env.hh"
#include "RowObserver.hh"

ShapeFactory::ShapeFactory(){};

ShapeFactory::~ShapeFactory(){};

std::list<BlockEntity *> ShapeFactory::GenerateBlocks(
    std::vector<sf::Vector2f *> positions,
    std::vector<std::vector<std::pair<int, int>>> coords,
    int size,
    sf::Vector2f pos, int type)
{
    std::list<BlockEntity *> blocks;

    sf::Texture *blockTexture = AssetsManager::getTexture("tiles");

    for (unsigned int i = 0; i < positions.size(); i++)
    {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(size, size));
        rect.setPosition(pos.x + positions.at(i)->x, pos.y + positions.at(i)->y);
        rect.setTexture(blockTexture);
        rect.setTextureRect(sf::IntRect(type * 18, 0, 18, 18));
        BlockEntity *block = new BlockEntity(rect);
        block->SetPosList(coords.at(i));
        blocks.push_back(block);
    }

    return blocks;
}


void GenerateSquareShape(std::vector<sf::Vector2f *> *positions, std::vector<std::vector<std::pair<int, int>>> *coords, int size) {
    positions->push_back(new sf::Vector2f(-size, 0));
    positions->push_back(new sf::Vector2f(0, 0));
    positions->push_back(new sf::Vector2f(0, -size));
    positions->push_back(new sf::Vector2f(-size, -size));
    coords->push_back({{-1, 0}, {0, -1}, {1, 0}, {0, 1}});
    coords->push_back({{0, 1}, {-1, 0}, {0, -1}, {1, 0}});
    coords->push_back({{1, 0}, {0, 1}, {-1, 0}, {0, -1}});
    coords->push_back({{0, -1}, {1, 0}, {0, 1}, {-1, 0}});
}

void GenerateLineShape(std::vector<sf::Vector2f *> *positions, std::vector<std::vector<std::pair<int, int>>> *coords, int size) {
    positions->push_back(new sf::Vector2f(-(2 * size), 0));
    positions->push_back(new sf::Vector2f(-size, 0));
    positions->push_back(new sf::Vector2f(0, 0));
    positions->push_back(new sf::Vector2f(size, 0));
    coords->push_back({{-2, -1}, {2, -2}, {1, 2}, {-1, 1}});
    coords->push_back({{-1, 0}, {1, -1}, {0, 1}, {0, 0}});
    coords->push_back({{0, 1}, {0, 0}, {-1, 0}, {1, -1}});
    coords->push_back({{1, 2}, {-1, 1}, {-2, -1}, {2, -2}});
}

void GenerateZShape(std::vector<sf::Vector2f *> *positions, std::vector<std::vector<std::pair<int, int>>> *coords, int size) {
    positions->push_back(new sf::Vector2f(size, 0));
    positions->push_back(new sf::Vector2f(0, 0));
    positions->push_back(new sf::Vector2f(0, size));
    positions->push_back(new sf::Vector2f(-size, size));
    coords->push_back({{1, 1}, {0, 1}, {-2, 0}, {1, -2}});
    coords->push_back({{0, 0}, {1, 0}, {-1, 1}, {0, -1}});
    coords->push_back({{-1, 1}, {0, -1}, {0, 0}, {1, 0}});
    coords->push_back({{-2, 0}, {1, -2}, {1, 1}, {0, 1}});
}

void GenerateReversedZShape(std::vector<sf::Vector2f *> *positions, std::vector<std::vector<std::pair<int, int>>> *coords, int size) {
    positions->push_back(new sf::Vector2f(size, 0));
    positions->push_back(new sf::Vector2f(0, 0));
    positions->push_back(new sf::Vector2f(0, -size));
    positions->push_back(new sf::Vector2f(-size, -size));
    coords->push_back({{1, 2}, {-2, 0}, {0, -1}, {1, -1}});
    coords->push_back({{0, 1}, {-1, -1}, {1, 0}, {0, 0}});
    coords->push_back({{1, 0}, {0, 0}, {0, 1}, {-1, -1}});
    coords->push_back({{0, -1}, {1, -1}, {1, 2}, {-2, 0}});
}

void GenerateLShape(std::vector<sf::Vector2f *> *positions, std::vector<std::vector<std::pair<int, int>>> *coords, int size) {
    positions->push_back(new sf::Vector2f(-(2 * size), 0));
    positions->push_back(new sf::Vector2f(-size, 0));
    positions->push_back(new sf::Vector2f(0, 0));
    positions->push_back(new sf::Vector2f(0, size));
    coords->push_back({{0, -1}, {2, -1}, {0, 2}, {-2, 0}});
    coords->push_back({{1, 0}, {1, 0}, {-1, 1}, {-1, -1}});
    coords->push_back({{2, 1}, {0, 1}, {-2, 0}, {0, -2}});
    coords->push_back({{1, 2}, {-1, 0}, {-1, -1}, {1, -1}});
}

void GenerateReversedLShape(std::vector<sf::Vector2f *> *positions, std::vector<std::vector<std::pair<int, int>>> *coords, int size) {
    positions->push_back(new sf::Vector2f(-(2 * size), 0));
    positions->push_back(new sf::Vector2f(-size, 0));
    positions->push_back(new sf::Vector2f(0, 0));
    positions->push_back(new sf::Vector2f(0, -size));
    coords->push_back({{-2, -1}, {0, -2}, {2, 1}, {0, 2}});
    coords->push_back({{-1, 0}, {-1, -1}, {1, 0}, {1, 1}});
    coords->push_back({{0, 1}, {-2, 0}, {0, -1}, {2, 0}});
    coords->push_back({{1, 0}, {-1, 1}, {-1, 0}, {1, -1}});
}

void GenerateTShape(std::vector<sf::Vector2f *> *positions, std::vector<std::vector<std::pair<int, int>>> *coords, int size) {
    positions->push_back(new sf::Vector2f(size, -size));
    positions->push_back(new sf::Vector2f(0, -size));
    positions->push_back(new sf::Vector2f(-size, -size));
    positions->push_back(new sf::Vector2f(0, 0));
    coords->push_back({{1, 1}, {-1, 1}, {-1, -1}, {1, -1}});
    coords->push_back({{0, 0}, {0, 0}, {0, 0}, {0, 0}});
    coords->push_back({{-1, -1}, {1, -1}, {1, 1}, {-1, 1}});
    coords->push_back({{-1, 1}, {-1, -1}, {1, -1}, {1, 1}});
}

AbstractEntity *ShapeFactory::Create(int type, const int &size, const sf::Vector2f &playablePos, int level)
{
    sf::Vector2f basePos = sf::Vector2f(playablePos.x - (4 * size), playablePos.y);
    std::vector<sf::Vector2f *> positions;
    std::vector<std::vector<std::pair<int, int>>> coords;

    switch (type)
    {
    case 1:
        GenerateSquareShape(&positions, &coords, size);
        break;

    case 2:
        GenerateLineShape(&positions, &coords, size);
        break;

    case 3:
        GenerateZShape(&positions, &coords, size);
        break;

    case 4:
        GenerateReversedZShape(&positions, &coords, size);
        break;

    case 5:
        GenerateLShape(&positions, &coords, size);
        break;

    case 6:
        GenerateReversedLShape(&positions, &coords, size);
        break;

    default:
        GenerateTShape(&positions, &coords, size);
        break;
    }

    std::list<BlockEntity *> blocks = GenerateBlocks(positions, coords, size, basePos, type);
    ShapeEntity *shape = new ShapeEntity(blocks, level);

    return shape;
}
