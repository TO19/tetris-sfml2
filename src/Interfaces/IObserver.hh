#ifndef IOBSERVER
#define IOBSERVER
#include <iostream>
#include "IObservable.hh"

class IObservable;

class IObserver {
    private:
    public:
        IObserver() {};
        virtual ~IObserver() {};
        virtual void Notify(IObservable*) = 0;
};

#endif /* IOBSERVER */
