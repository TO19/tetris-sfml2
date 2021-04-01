#ifndef SCENE /* SCENE */
#define SCENE

#include <iostream>
#include "AbstractEntity.hh"
#include "TimeManager.hh"
#include <list>
#include <SFML/Graphics.hpp>
#include "ShapeEntity.hh"
#include "PlayableArea.hh"
#include "AssetsManager.hh"
#include "ShapeFactory.hh"
#include "RowObserver.hh"
#include "SoundManager.hh"
#include "TxtFileManager.hh"
class Scene
{
private:
    sf::Text _fpsCounter;
    sf::Text _scoreText;
    PlayableArea *_playableArea;
    std::list<AbstractEntity *> _entityList;
    int _level = 1;
    bool CheckBlockCollision(ShapeEntity *, BlockEntity *, std::list<AbstractEntity *>, bool);
    void PlaceInGame(ShapeEntity *);
    void UpdateFPS();
    void UpdateScoreText();
    void UpdatePlayableArea();
    void UpdateLevel();
    void UpdateBackground();
    void UpdateGameOverText();
    void UpdateLeaderBoard();
    bool _gameRunning = true;

protected:
    sf::RenderWindow *_window;

public:
    Scene(sf::RenderWindow *);
    ~Scene();

    std::list<AbstractEntity *> GetEntities() const;
    bool CheckPlayableAreaCollision(ShapeEntity *, bool);
    void AddEntity(AbstractEntity *);
    AbstractEntity *GetEntity(int index);
    void RemoveEntity(AbstractEntity *);
    void Update();
    void CleanEntities();
    sf::RenderWindow *GetWindow();
    PlayableArea *GetPlayableArea() const;
    void SetPlayableArea(PlayableArea *playableArea);
    void GenerateShape();
    void SetGameRunning(bool);
};

#endif /* SCENE */