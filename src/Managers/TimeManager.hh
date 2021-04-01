#ifndef TIMEMANAGER
#define TIMEMANAGER
#include <iostream>
#include <chrono>

class TimeManager
{
private:
    TimeManager();
    int _begin = 0;
    int _update = 0;
    int _elapsed = 0;
    static TimeManager *_instance;

public:
    static TimeManager *GetInstance();
    virtual ~TimeManager();
    virtual void Start();
    virtual void Update();
    unsigned int GetElapsedTime() const;
    unsigned int GetStartedTime() const;
    unsigned int GetBeginTime() const;
    TimeManager(TimeManager const &) = delete;
    TimeManager &operator=(TimeManager const &) = delete;
};

#endif /* TIMEMANAGER */
