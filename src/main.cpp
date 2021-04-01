#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <functional>
#include "TimeManager.hh"
#include "Scene.hh"
#include "ShapeFactory.hh"
#include "env.hh"
#include <math.h>
#include "ShapeEntity.hh"
#include "TxtFileManager.hh"
#include "Menu.hh"
#include "State.hh"

// Calculer la distance entre 2 points (x,y)
float calculateDistance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

float calculateAreaCircle(float radius)
{
    return 3.14 * radius * radius;
}

void PlaceInGame(Scene *scene, ShapeEntity *shape)
{
    shape->SetMoving(true);
    shape->SetPreview(false);
    shape->SetPosition(scene->GetPlayableArea()->GetBasePos());
}

void handleEvent(Scene *scene, State *state)
{
    sf::Event event;
    while (scene->GetWindow()->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            scene->GetWindow()->close();

        auto entityList = scene->GetEntities();
        ShapeEntity *currentShape = dynamic_cast<ShapeEntity *>(scene->GetEntity(1));
        auto gridSize = scene->GetPlayableArea()->GetGridSize();

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::P)
                state->SetState(0);
            if (event.key.code == sf::Keyboard::Escape)
                scene->GetWindow()->close();
            if (event.key.code == sf::Keyboard::Space)
                scene->CleanEntities();

            if (event.key.code == sf::Keyboard::Right)
            {
                currentShape->TranslateX(-gridSize);

                if (scene->CheckPlayableAreaCollision(currentShape, true))
                {
                    currentShape->MoveX(gridSize);
                }
            }
            if (event.key.code == sf::Keyboard::Left)
            {
                currentShape->TranslateX(gridSize);

                if (scene->CheckPlayableAreaCollision(currentShape, true))
                {
                    currentShape->MoveX(-gridSize);
                }
            }
            if (event.key.code == sf::Keyboard::Up)
            {
                currentShape->Turn();

                if (scene->CheckPlayableAreaCollision(currentShape, true))
                {
                    currentShape->RevertTurn();
                }
            }
            if (event.key.code == sf::Keyboard::Down)
            {
                currentShape->SetSpeed(currentShape->GetSlowSpeed() * 5);
            }

            if (event.key.code == sf::Keyboard::R)
            {
                scene->CleanEntities();
                scene->SetGameRunning(true);
                scene->GetPlayableArea()->SetScore(0);
                scene->GenerateShape();
            }
        }

        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Down)
            {
                currentShape->SetSpeed(currentShape->GetSlowSpeed());
            }
        }
    }
}

void handleEventM(Menu *menu, State *state)
{
    sf::Event event;
    while (menu->GetWindow()->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            menu->GetWindow()->close();
        }

        // Clic New Game
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            std::cout << "[INFO] Starting new game" << std::endl;
            if (menu->GetBoundNG().contains(sf::Mouse::getPosition(*menu->GetWindow()).x, sf::Mouse::getPosition(*menu->GetWindow()).y))
            {
                state->SetState(1);
            }
            else if (menu->GetBoundE().contains(sf::Mouse::getPosition(*menu->GetWindow()).x, sf::Mouse::getPosition(*menu->GetWindow()).y))
            {
                menu->GetWindow()->close();
            }
        }

        // Clic Leaderboard
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (menu->GetBoundL().contains(sf::Mouse::getPosition(*menu->GetWindow()).x, sf::Mouse::getPosition(*menu->GetWindow()).y))
            {
                std::cout << "Leaderboard" << std::endl;
            }
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(resolution_x, resolution_y), "Tetris IDVCPP4", sf::Style::Titlebar | sf::Style::Close);
    State *state = new State();

    window.setFramerateLimit(max_framerate);
    TimeManager *time = TimeManager::GetInstance();
    time->Start();

    SoundManager *sounds = new SoundManager();
    sounds->playTetrisMusic();

    Scene *scene = new Scene(&window);
    auto playableArea = new PlayableArea(&window);
    scene->SetPlayableArea(playableArea);

    Menu *menu = new Menu(&window);

    while (window.isOpen())
    {
        switch (state->GetState())
        {
        case MENU:
        {
            handleEventM(menu, state);
            menu->Update();
            break;
        }

        case GAME:
        {
            handleEvent(scene, state);
            scene->Update();
            break;
        }

        default:
        {
            std::cout << "Default state 19" << std::endl;
            break;
        }
        }
    }
    return 0;
}