#include "TimeManager.hh"
#include <unistd.h>
TimeManager::TimeManager(){};
TimeManager::~TimeManager(){};
TimeManager *TimeManager::_instance = 0;

void TimeManager::Start()
{
    int now = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::system_clock::now().time_since_epoch())
                  .count();
    this->_begin = now;
    this->_update = now;
};

void TimeManager::Update()
{
    int now = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::system_clock::now().time_since_epoch())
                  .count();
    if (this->_update == 0)
    {
        this->_update = now;
    }
    else
    {
        this->_elapsed = now - this->_update;
        this->_update = now;
    }
};

unsigned int TimeManager::GetElapsedTime() const
{
    return this->_elapsed;
}

unsigned int TimeManager::GetStartedTime() const
{
    return this->_update - this->_begin;
}

unsigned int TimeManager::GetBeginTime() const
{
    return this->_begin;
}


TimeManager *TimeManager::GetInstance()
{

    if (_instance == 0)
    {
        _instance = new TimeManager();
    }

    return _instance;
}