#ifndef ROWOBSERVER
#define ROWOBSERVER
#include "Interfaces/IObserver.hh"
#include "ShapeEntity.hh"
#include "PlayableArea.hh"

class RowObserver : public IObserver
{
private:
    PlayableArea *_area;
    std::list<AbstractEntity *> _entities;
    void DeleteFullRow(std::vector<BlockEntity *>);

public:
    RowObserver(
        PlayableArea *_area,
        std::list<AbstractEntity *> _entities);
    ~RowObserver(){};
    void MakeShapesFall(double);
    virtual void Notify(IObservable *);
};

#endif /* ROWOBSERVER */
