#include "../include/GameStateManager.hpp"
#include "GameState.hpp"

void GameStateManager::changeState(std::unique_ptr<GameState> newState)
{
    if (!states.empty())
        states.pop();                 // Retirer l'état actuel
    states.push(std::move(newState)); // Ajouter le nouvel état
}

void GameStateManager::update()
{
    if (!states.empty())
        states.top()->update();
}

void GameStateManager::handleInput(sf::RenderWindow &window)
{
    if (!states.empty())
        states.top()->handleInput(window);
}

void GameStateManager::render(sf::RenderWindow &window)
{
    if (!states.empty())
        states.top()->render(window);
}
