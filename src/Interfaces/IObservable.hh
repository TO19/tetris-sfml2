#ifndef IOBSERVABLE
#define IOBSERVABLE
#include <iostream>
#include "IObserver.hh"
#include <list>

class IObserver;

class IObservable {
    public:
        std::list<IObserver *> _observers;
        IObservable() {};
        virtual ~IObservable() {};
        virtual void AddObserver(IObserver*) = 0;
        virtual void RemoveObserver(IObserver*) = 0;
};

#endif /* IOBSERVABLE */
