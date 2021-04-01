#ifndef PLAYABLEAREA
#define PLAYABLEAREA
#include <SFML/Graphics.hpp>
#include <iostream>

class PlayableArea
{
private:
    sf::RectangleShape _area;
    sf::Vector2f _basePos;
    int _gridSize;
    sf::Texture bg;
    int _score = 0;

public:
    PlayableArea(sf::RenderWindow *);
    ~PlayableArea();

    sf::RectangleShape GetArea() const;
    void SetArea(sf::RectangleShape);

    int GetGridSize() const;
    void SetGridSize(int);
    sf::Vector2f GetBasePos() const;
    int GetMaxBlocks() const;

    double GetClosestSnap(double) const;

    int GetScore() const;
    void SetScore(int);
    void AddScore(int);
    void AddRowsScore(int);
};

#endif /* PLAYABLEAREA */
