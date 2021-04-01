#ifndef STATE
#define STATE
#include <SFML/Graphics.hpp>

class State
{
private:
    /* No private fields for the moment */
    int _state = 0;

public:
    State();
    ~State();
    void SetState(int);
    int GetState();
};

#endif /* STATE */