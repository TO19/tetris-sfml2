#ifndef SHAPEENTITY
#define SHAPEENTITY

#include <iostream>
#include "Movable.hh"
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <list>
#include "BlockEntity.hh"
#include "../Interfaces/IObservable.hh"

class ShapeEntity : public Movable, public IObservable
{
private:
    int _size;
    sf::Color _color;
    std::list<BlockEntity *> _blockList;
    int _currentRotation = 0;
    int _lastRotation = 0;
    double _slowSpeed;
    bool _isPreview = true;

    void TurnBlocks(bool);
    void SetSlowSpeed(double);

protected:
    void NotifyAllObservers();

public:
    ShapeEntity(std::list<BlockEntity *>, int);
    ShapeEntity();

    virtual void Draw(sf::RenderWindow *);
    virtual void Update();
    virtual void UpdatePosition();

    virtual void AddObserver(IObserver *);
    virtual void RemoveObserver(IObserver *);

    virtual void SetX(double);
    virtual void SetY(double);
    void SetPosition(sf::Vector2f);

    int GetSize() const;
    void SetSize(int);

    void SetPreview(bool);
    bool isPreview() const; // easier to understand but basically just a getter

    double GetSlowSpeed() const;

    void MoveX(double);
    void TranslateX(double);
    void TranslateY(double);
    bool CheckPlayableAreaCollision(ShapeEntity *);

    std::list<BlockEntity *> GetBlockList() const;
    void RemoveBlock(BlockEntity *);
    void Turn();
    void RevertTurn();
    void Freeze();
};

#endif /* SHAPEENTITY */