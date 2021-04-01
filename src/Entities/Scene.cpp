#include "Scene.hh"
#include "env.hh"

Scene::Scene(sf::RenderWindow *window)
{
    AssetsManager::loadFont("main", MAIN_FONT_PATH);
    AssetsManager::loadTexture("tiles", TILES_PNG);
    AssetsManager::loadTexture("windowBg", WINDOW_BG);

    sf::Font *main = AssetsManager::getFont("main");

    _fpsCounter.setFont(*main);
    _fpsCounter.setCharacterSize(framerate_font_size);
    _fpsCounter.setFillColor(sf::Color::Red);
    _fpsCounter.setStyle(sf::Text::Bold);

    _scoreText.setFont(*main);
    _scoreText.setCharacterSize(score_font_size);
    _scoreText.setPosition(100, 100);
    _scoreText.setFillColor(sf::Color::Green);

    this->_window = window;
};

Scene::~Scene(){};

std::list<AbstractEntity *> Scene::GetEntities() const
{
    return this->_entityList;
}

void Scene::UpdateLevel()
{
    if (this->_playableArea->GetScore() >= (this->_level * LEVEL_MULTIPLIER))
    {
        this->_level += 1;
    }
}

sf::RenderWindow *Scene::GetWindow()
{
    return this->_window;
}

void Scene::CleanEntities()
{
    this->_entityList.clear();
}

void Scene::AddEntity(AbstractEntity *entity)
{
    this->_entityList.push_front(entity);
}

void Scene::UpdateScoreText()
{
    this->_scoreText.setString(std::to_string(this->_playableArea->GetScore()));
    this->_window->draw(this->_scoreText);
}

void Scene::UpdateFPS()
{
    int fps = 1000 / (int)TimeManager::GetInstance()->GetElapsedTime();
    int maxFramerate = max_framerate - WINDOW_FPS_SFML_BUG; // SFML set max fps unreliable so we make a fake cap.
    if (fps > maxFramerate)
    {
        fps = maxFramerate;
    }
    this->_fpsCounter.setString(std::to_string(fps));
    this->_window->draw(this->_fpsCounter);
}

void Scene::UpdateBackground()
{
    sf::Texture *backgroundTexture = AssetsManager::getTexture("windowBg");

    sf::Vector2u textureSize = backgroundTexture->getSize();
    sf::Vector2u windowSize = this->_window->getSize();

    float scaleX = (float)windowSize.x / (float)textureSize.x;
    float scaleY = (float)windowSize.y / (float)textureSize.y;

    sf::Sprite background;
    background.setTexture(*backgroundTexture);
    background.setScale(scaleX, scaleY);
    this->_window->draw(background);
}

void Scene::UpdatePlayableArea()
{
    this->_window->draw(this->_playableArea->GetArea());
}

void Scene::RemoveEntity(AbstractEntity *entity)
{
    this->_entityList.remove(entity);
}

AbstractEntity *Scene::GetEntity(int index)
{
    std::list<AbstractEntity *>::iterator it = this->_entityList.begin();
    std::advance(it, index);
    return *it;
}

void Scene::
    Update()
{
    this->_window->clear();
    TimeManager::GetInstance()->Update();
    UpdateBackground();
    UpdateFPS();
    UpdateScoreText();
    UpdatePlayableArea();
    UpdateLeaderBoard();
    UpdateLevel();
    std::list<AbstractEntity *>::iterator it;

    for (it = this->_entityList.begin(); it != this->_entityList.end(); ++it)
    {
        ShapeEntity *shape = dynamic_cast<ShapeEntity *>(*it);
        if (shape != NULL && !CheckPlayableAreaCollision(shape, false))
        {
            (*it)->Update();
        }
        (*it)->Draw(this->_window);
    }

    if (!this->_gameRunning)
    {
        UpdateGameOverText();
    }
    this->_window->display();
}

PlayableArea *Scene::GetPlayableArea() const
{
    return this->_playableArea;
}

void Scene::SetPlayableArea(PlayableArea *playableArea)
{
    this->_playableArea = playableArea;
}

bool Scene::CheckBlockCollision(
    ShapeEntity *movingEntity,
    BlockEntity *movingBlock,
    std::list<AbstractEntity *> entityList,
    bool isXTranslation)
{
    sf::RectangleShape movingRect = movingBlock->GetBlock();
    auto currentBounds = movingRect.getGlobalBounds();

    if (entityList.size() > 1)
    {
        for (auto shape : entityList)
        {
            auto shapeEntity = dynamic_cast<ShapeEntity *>(shape);
            if (shapeEntity != movingEntity)
            {
                for (auto staticBlock : shapeEntity->GetBlockList())
                {
                    sf::RectangleShape staticRect = staticBlock->GetBlock();
                    auto staticRectBounds = staticRect.getGlobalBounds();

                    if (currentBounds.intersects(staticRectBounds))
                    {
                        if (!isXTranslation)
                        {

                            double snapPos = GetPlayableArea()->GetClosestSnap(-movingRect.getPosition().y);
                            movingEntity->TranslateY(movingRect.getPosition().y + snapPos);
                            movingEntity->Freeze();
                            if (this->_gameRunning)
                            {
                                GenerateShape();
                            }
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Scene::CheckPlayableAreaCollision(ShapeEntity *shape, bool isXTranslation)
{
    if (shape->GetMoving())
    {
        sf::RectangleShape area = GetPlayableArea()->GetArea();
        auto playableAreaBounds = area.getGlobalBounds();
        for (auto movingBlock : shape->GetBlockList())
        {
            sf::RectangleShape movingRect = movingBlock->GetBlock();
            auto movingRectBounds = movingRect.getGlobalBounds();

            if (CheckBlockCollision(shape, movingBlock, this->_entityList, isXTranslation))
            {
                if (GetPlayableArea()->GetGridSize() <= shape->GetY() && this->_gameRunning)
                {
                    auto sounds = new SoundManager();
                    sounds->playGameOver();
                    TxtFileManager::writeToFile("./Assets/score.txt", "LocalPlayer " + std::to_string(GetPlayableArea()->GetScore()));
                    this->_gameRunning = false;
                }

                return true;
            }

            /* If bounds in playable area we don't have a problem we do have one */
            if (!playableAreaBounds.intersects(movingRectBounds) ||
                movingRectBounds.top + movingRectBounds.height > playableAreaBounds.height + area.getPosition().y)
            {
                if (movingRectBounds.top > playableAreaBounds.height)
                {
                    double snapPos = GetPlayableArea()->GetClosestSnap(-movingRect.getPosition().y);
                    shape->TranslateY(movingRect.getPosition().y + snapPos);
                    shape->Freeze();
                    if (this->_gameRunning)
                    {
                        GenerateShape();
                    }
                }
                return true;
            }
        }
    }
    return false;
}

void Scene::PlaceInGame(ShapeEntity *shape)
{
    shape->SetMoving(true);
    shape->SetPreview(false);
    /* TODO Temporary thing, setPosition must be bugged, and shapes don't have the same origin */
    shape->SetPosition(sf::Vector2f(GetPlayableArea()->GetBasePos().x, GetPlayableArea()->GetGridSize()));
}

void Scene::GenerateShape()
{
    ShapeFactory *factory = new ShapeFactory();

    int size = GetPlayableArea()->GetGridSize();
    sf::Vector2f playablePos = GetPlayableArea()->GetArea().getPosition();

    auto *shapeAsAbstractEntity = factory->Create(rand() % 7, size, playablePos, this->_level);
    auto shape = dynamic_cast<ShapeEntity *>(shapeAsAbstractEntity);
    if (NULL != shape)
    {

        if (GetEntities().size() == 0)
        {
            /* Generate Next Shape */
            AddEntity(shape);
            GenerateShape(); // Playable one
            return;
        }

        AddEntity(shape);
        /* Add Observers here */

        shape->AddObserver(new RowObserver(GetPlayableArea(), this->_entityList));
        PlaceInGame(dynamic_cast<ShapeEntity *>(GetEntity(1)));
    }
}

void Scene::UpdateGameOverText()
{
    sf::Text gameOverText;
    gameOverText.setFont(*AssetsManager::getFont("main"));
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setString("Game over - Press R to restart");
    gameOverText.setPosition(
        GetWindow()->getSize().x / 5,
        GetWindow()->getSize().y / 2);
    this->_window->draw(gameOverText);
}

void Scene::UpdateLeaderBoard()
{
    const int LEFT_MARGIN = 25;
    const int TOP_MARGIN = 419;
    auto list = TxtFileManager::readScoreboardFile();
    int counter = 1;

    sf::Text leaderBoard;
    leaderBoard.setFont(*AssetsManager::getFont("main"));
    leaderBoard.setCharacterSize(40);
    leaderBoard.setStyle(sf::Text::Underlined | sf::Text::Bold);
    leaderBoard.setFillColor(sf::Color::White);
    leaderBoard.setString("Leaderboard: ");
    leaderBoard.setPosition(LEFT_MARGIN, TOP_MARGIN - 20);

    for (auto score : list)
    {
        std::string name = score.first += " ";
        std::string nameAndScore = name += std::to_string(score.second);
        sf::Text text;
        text.setFont(*AssetsManager::getFont("main"));
        text.setCharacterSize(25);
        text.setFillColor(sf::Color::White);
        text.setString(nameAndScore);
        text.setPosition(LEFT_MARGIN, (counter * 25) + TOP_MARGIN);
        this->_window->draw(text);
        counter++;
    }
    this->_window->draw(leaderBoard);
}

void Scene::SetGameRunning(bool isRunning)
{
    this->_gameRunning = isRunning;
}