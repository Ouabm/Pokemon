#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class GameStateManager;

class GameState
{
public:
    virtual ~GameState() = default;
    virtual void handleInput(sf::RenderWindow &window) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow &window) = 0;

protected:
    GameState(GameStateManager *manager) : gameManager(manager) {}

    GameStateManager *gameManager;
};
