#include "Movable.hh"

void Movable::Draw(sf::RenderWindow *){};

void Movable::Update(){};

void Movable::UpdatePosition() {}

double Movable::GetX() const
{
    return this->_x;
}
void Movable::SetX(double x)
{
    this->_x = x;
}
double Movable::GetY() const
{
    return this->_y;
}
void Movable::SetY(double y)
{
    this->_y = y;
}

double Movable::GetDirection() const {
    return this->_direction;
}

void Movable::SetDirection(double direction) {
    this->_direction = direction;
}

double Movable::GetSpeed() const {
    return this->_speed;
}

void Movable::SetSpeed(double speed) {
    this->_speed = speed;
}

bool Movable::GetMoving() const {
    return this->_moving;
}

void Movable::SetMoving(bool moving) {
    this->_moving = moving;
}