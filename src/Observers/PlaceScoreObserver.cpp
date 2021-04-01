#include "PlaceScoreObserver.hh"

PlaceScoreObserver::PlaceScoreObserver(PlayableArea *area)
{
    this->_area = area;
};

void PlaceScoreObserver::Notify(IObservable *observable){
    (void)observable;
}