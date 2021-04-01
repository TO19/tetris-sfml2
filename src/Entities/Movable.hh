#ifndef MOVABLE
#define MOVABLE
#include <iostream>
#include "Abstract/AbstractEntity.hh"
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "env.hh"

class Movable : public AbstractEntity
{
protected:
    double _x = 0;
    double _y = 0;
    double _direction;
    bool _moving = false;
    double _speed; // in px / second
    virtual void UpdatePosition();

public:
    Movable(){};
    virtual ~Movable(){};

    virtual void Draw(sf::RenderWindow *);
    virtual void Update();
    virtual double GetX() const;
    virtual void SetX(double);
    virtual double GetY() const;
    virtual void SetY(double);
    double GetDirection() const;
    void SetDirection(double);
    double GetSpeed() const;
    void SetSpeed(double);
    bool GetMoving() const;
    void SetMoving(bool);
};

#endif /* MOVABLE */
