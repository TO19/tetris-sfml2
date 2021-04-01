#include "State.hh"

State::State(){}

void State::SetState(int state)
{
    this->_state = state;
}

int State::GetState()
{
    return this->_state;
}

State::~State(){}