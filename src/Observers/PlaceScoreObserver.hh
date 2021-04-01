#ifndef PLACESCOREOBSERVER
#define PLACESCOREOBSERVER
#include "IObserver.hh"
#include "PlayableArea.hh"
#include "ShapeEntity.hh"

class PlaceScoreObserver : public IObserver
{
private:
    PlayableArea *_area;

public:
    PlaceScoreObserver(PlayableArea *);
    ~PlaceScoreObserver(){};
    virtual void Notify(IObservable *);
};

#endif /* PLACESCOREOBSERVER */
