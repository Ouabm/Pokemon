#pragma once

#include <SFML/Graphics.hpp>
#include <stack>
#include <memory>

#include "GameState.hpp"

class GameStateManager
{
public:
    void changeState(std::unique_ptr<GameState> newState);
    void update();
    void handleInput(sf::RenderWindow &window);
    void render(sf::RenderWindow &window);

private:
    std::stack<std::unique_ptr<GameState>> states;
};